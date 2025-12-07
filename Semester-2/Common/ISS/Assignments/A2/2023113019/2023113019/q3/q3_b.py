import urllib.request
import re
from bs4 import BeautifulSoup
import time
import json
import sqlite3
import matplotlib.pyplot as plt
from wordcloud import WordCloud


def createTable():
    conn = sqlite3.connect('top_250.db')
    cursor = conn.cursor()
    create_table_query = """
        CREATE TABLE IF NOT EXISTS shows (
            id INTEGER PRIMARY KEY,
            Title TEXT,
            Genre TEXT,
            Episodes INTEGER,
            Rating REAL
        )
    """
    cursor.execute(create_table_query)
    conn.commit()
    conn.close()
    conn.close()

def connectToSite():
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3'}
    url = "https://www.imdb.com/chart/toptv/?ref_=nv_tvv_250"
    req = urllib.request.Request(url, headers=headers)
    page = urllib.request.urlopen(req)
    html_bytes = page.read()
    html = html_bytes.decode("utf-8")
    soup = BeautifulSoup(html, "html.parser")
    return soup


def insertTitles(soup):
    conn = sqlite3.connect('top_250.db')
    cursor = conn.cursor()
    div_tags = soup.find_all('div',
                             class_='ipc-title ipc-title--base ipc-title--title ipc-title-link-no-icon ipc-title--on-textPrimary sc-be6f1408-9 srahg cli-title')
    for div_tag in div_tags:
        h3_tag = div_tag.find('h3', class_='ipc-title__text')
        if h3_tag:
            text = h3_tag.text.strip()
            dot_space_index = text.find('. ')
            if dot_space_index != -1:
                stripped_text = text[dot_space_index + 2:]
                insert_query = "INSERT INTO shows (Title) VALUES (?)"
                cursor.execute(insert_query, (stripped_text,))
    conn.commit()


def updateEpisodes(soup):
    conn = sqlite3.connect('top_250.db')
    cursor = conn.cursor()
    span_tags = soup.find_all('span', class_='sc-be6f1408-8 fcCUPU cli-title-metadata-item')
    pattern = r'\d+\s+eps'
    show_id = 1
    for span_tag in span_tags:
        span_text = span_tag.text.strip()
        match = re.search(pattern, span_text)
        if match:
            text_before_space = span_text.split()[0]
            ep_num = int(text_before_space)
            update_query = "UPDATE shows SET Episodes = ? WHERE id = ?"
            cursor.execute(update_query, (ep_num, show_id))
            show_id += 1
    conn.commit()


def updateRating(soup):
    conn = sqlite3.connect('top_250.db')
    cursor = conn.cursor()
    span_tags = soup.find_all('span',
                              class_='ipc-rating-star ipc-rating-star--base ipc-rating-star--imdb ratingGroup--imdb-rating')
    show_id = 1
    for span_tag in span_tags:
        span_text = span_tag.text.strip()
        first_word = span_text.split()[0]
        rating = float(first_word)
        update_query = "UPDATE shows SET Rating = ? WHERE id = ?"
        cursor.execute(update_query, (rating, show_id))
        show_id += 1
    conn.commit()


def updateGenre(soup):
    conn = sqlite3.connect('top_250.db')
    cursor = conn.cursor()
    script_tag = soup.find('script', id='__NEXT_DATA__')
    if script_tag:
        script_content = script_tag.string
        if script_content:
            data = json.loads(script_content)
            chart_titles_edges = data['props']['pageProps']['pageData']['chartTitles']['edges']
            show_id = 1
            for edge in chart_titles_edges:
                title_genres_data = edge['node']['titleGenres']['genres']
                genres_string = ' '.join(genre['genre']['text'] for genre in title_genres_data)
                update_query = "UPDATE shows SET Genre = ? WHERE id = ?"
                cursor.execute(update_query, (genres_string, show_id))
                show_id += 1
    conn.commit()


def selectShows():
    genre_input = input("Enter the genre: ")
    genre_list = genre_input.split()
    rating_lower_limit, rating_upper_limit = input("Enter the rating range: ").split()
    episodes_lower_limit, episodes_upper_limit = input("Enter the episodes range: ").split()
    connection = sqlite3.connect('top_250.db')
    cursor = connection.cursor()

    # cursor.execute(use_database_query)
    select_query = "SELECT Title,Rating FROM shows WHERE ("
    for i, genre in enumerate(genre_list):
        if i != 0:
            select_query += " OR "
        select_query += f"Genre LIKE '%{genre}%'"

    select_query += ")"
    select_query += " AND Rating >= ? AND Rating <= ? AND Episodes >= ? AND Episodes <= ?"
    select_query += " ORDER BY Rating DESC"
    cursor.execute(select_query, (rating_lower_limit, rating_upper_limit, episodes_lower_limit, episodes_upper_limit))
    result = cursor.fetchall()
    shows_dict = {title: rating for title, rating in result}
    if result:
        print(
            f"Shows with genre '{genre_input}' and rating between {rating_lower_limit} and {rating_upper_limit} and episodes between {episodes_lower_limit} and {episodes_upper_limit} are:")
        for row in result:
            print(row[0])

    connection.close()

if __name__=="__main__":
    createTable()
    soup = connectToSite()
    insertTitles(soup)
    updateEpisodes(soup)
    updateRating(soup)
    updateGenre(soup)
    shows_dict = selectShows()