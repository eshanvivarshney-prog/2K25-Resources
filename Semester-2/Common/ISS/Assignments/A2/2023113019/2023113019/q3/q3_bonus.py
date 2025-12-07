import urllib.request
import re
from bs4 import BeautifulSoup
import time
import json
import sqlite3
import matplotlib.pyplot as plt
from wordcloud import WordCloud


def selectShows():
    genreInput = input("Enter the genre: ")
    genreList = genreInput.split()
    ratingLowerLimit, ratingUpperLimit = input("Enter the rating range: ").split()
    episodesLowerLimit, episodesUpperLimit = input("Enter the episodes range: ").split()
    connection = sqlite3.connect('../top_250.db')
    cursor = connection.cursor()

    selectQuery = "SELECT Title,Rating FROM shows WHERE ("
    for i, genre in enumerate(genreList):
        if i != 0:
            selectQuery += " OR "
        selectQuery += f"Genre LIKE '%{genre}%'"

    selectQuery += ")"
    selectQuery += " AND Rating >= ? AND Rating <= ? AND Episodes >= ? AND Episodes <= ?"
    selectQuery += " ORDER BY Rating DESC"
    cursor.execute(selectQuery, (ratingLowerLimit, ratingUpperLimit, episodesLowerLimit, episodesUpperLimit))
    result = cursor.fetchall()
    showsDict = {title: rating for title, rating in result}

    connection.close()
    return showsDict


def generateWordCloud(showsDict):
    wordcloud = WordCloud(width=800, height=400, background_color='white', max_words=150).generate_from_frequencies(
        showsDict)
    plt.figure(figsize=(10, 8))
    plt.imshow(wordcloud, interpolation='bilinear')
    plt.axis('off')
    plt.savefig('wordcloudbonus.png')
    # plt.show()

showsDict = selectShows()

generateWordCloud(showsDict)
