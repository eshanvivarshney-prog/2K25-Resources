from flask import Flask, request, render_template, redirect, url_for
from genericpath import isfile
import json
import hashlib

app = Flask(__name__)

# hash password
def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

users = []
def write():
    with open('users.txt', 'w') as file:
        file.write(json.dumps(users))

#initial load
if(not isfile('users.txt')):
    write()

users = json.loads(open('users.txt').read())

def getuser(email):
    for user in users:
        if user['email'] == email:
            return user
    return None

# registration form
@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        name = request.form['name']
        email = request.form['email']
        password = hash_password(request.form['password'])
        if(getuser(email)):
            return 'User already exists'
        else:
            users.append({'name': name, 'email': email, 'password': password})
            write()
        return redirect(url_for('success'))
    return render_template('register.html')

@app.route('/success')
def success():
    return render_template('success.html')

@app.route('/user/<user_id>')
def user(user_id):
    if(user := getuser(user_id)):
        return render_template('user.html', user=user)
    else:
        return 'User not found'

if __name__ == '__main__':
    app.run(debug=True)

