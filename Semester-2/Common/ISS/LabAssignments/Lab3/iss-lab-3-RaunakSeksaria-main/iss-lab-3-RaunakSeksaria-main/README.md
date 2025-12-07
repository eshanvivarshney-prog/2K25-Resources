# Flask Registration Application

## Overview
This application provides a simple user registration system using Flask.

## Functionality
- User registration with name, email, and password.
- Passwords are decrypted for security.
- User details are stored in 'users.txt' in JSON format.
- A route to display registered user details.

## Usage
1. Run `app.py` to start the Flask server.
2. Access the root URL for registration.
3. Visit '/user/<user_id>' to view user details.

## Assumptions
- User ID is assumed to be the user's name.
- It is assumed that User ID are unique
