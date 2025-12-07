import urllib.request
import re
from bs4 import BeautifulSoup
import time
import json
import matplotlib.pyplot as plt
import sqlite3


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


def plotGenre():
    conn = sqlite3.connect('top_250.db')
    cursor = conn.cursor()
    cursor.execute("SELECT Genre FROM shows")
    result = cursor.fetchall()
    genre_dict = dict()
    for row in result:
        temp_list = row[0].split()
        for genre in temp_list:
            if genre in genre_dict:
                genre_dict[genre] += 1
            else:
                genre_dict[genre] = 1
    genre_item = genre_dict.keys()
    genre_count = genre_dict.values()
    plt.bar(genre_item, genre_count)
    plt.xticks(rotation=90)
    # plt.figure().set_figheight(100)
    # plt.figure(figsize=(80, 60))
    plt.xlabel('Genre', fontsize=0.3)
    plt.ylabel('Number of shows')
    # fig = plt.figure(constrained_layout=True)
    # fig.tight_layout()
    # fig.savefig('a.png', bbox_inches='tight')
    plt.title('Genre vs Number of shows')
    plt.savefig('genre_plotting.png', bbox_inches='tight')

def plotEpisodes():
    conn = sqlite3.connect('top_250.db')
    cursor = conn.cursor()
    cursor.execute("SELECT MAX(episodes) AS max_episodes, MIN(episodes) AS min_episodes FROM shows")
    result = cursor.fetchone()
    max_episodes = result[0]
    min_episodes = result[1]
    episode_list = []
    # print(min_episodes, max_episodes)
    # print(result)
    for i in range(min_episodes, max_episodes + 1):
        cursor.execute("SELECT COUNT(*) FROM shows WHERE episodes = ?", (i,))
        result = cursor.fetchone()
        # print(result)
        episode_list.append(result[0])

    # print(episode_list)
    plt.plot(range(min_episodes, max_episodes + 1), episode_list)
    plt.xlabel('Episodes')
    plt.ylabel('Number of shows')
    plt.title('Episodes vs Number of shows')
    plt.savefig('episode_plotting.png')
    # plt.show()
    conn.commit()

if __name__ == '__main__':
    createTable()
    soup = connectToSite()
    insertTitles(soup)
    updateEpisodes(soup)
    updateRating(soup)
    updateGenre(soup)
    plotGenre()
    plotEpisodes()
