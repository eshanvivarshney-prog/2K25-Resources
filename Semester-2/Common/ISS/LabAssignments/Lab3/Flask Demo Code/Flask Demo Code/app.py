from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'secret_key_for_flash_messages'

posts = [
    {
        'title': 'This is Post-1',
        'content': 'This is content of Post-1',
        'author': 'Author-1'
    },
    {
        'title': 'This is Post-2',
        'content': 'This is content of Post-2',
        'author': 'Author-2'
    },
]

@app.route('/')
def home():
    return render_template('home.html', posts=posts)

# Route for displaying a specific post
@app.route('/post/<int:post_id>')
def show_post(post_id):
    if 0 <= post_id < len(posts):
        post = posts[post_id]
        return render_template('post.html', post=post)
    else:
        return redirect(url_for('home'))

# Route for adding a new post
@app.route('/add_post', methods=['GET', 'POST'])
def add_post():
    if request.method == 'POST':
        title = request.form['title']
        content = request.form['content']
        author = request.form['author']

        new_post = {'title': title, 'content': content, 'author': author}
        posts.append(new_post)

        flash('Post added successfully!', 'success')
        return redirect(url_for('home'))

    return render_template('add_post.html')

# Error handling for 404
@app.errorhandler(404)
def page_not_found(error):
    return render_template('404.html'), 404

if __name__ == '__main__':
    app.run(debug=True)
