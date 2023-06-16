# #!/usr/bin/env python3
# import cgi
# import http.cookies as Cookies

# # Function to set the background color cookie
# def set_color_cookie(color):
#     cookie = Cookies.SimpleCookie()
#     cookie['bgcolor'] = color
#     cookie['bgcolor']['path'] = '/'
#     cookie['bgcolor']['expires'] = 24 * 60 * 60  # 1 day
#     print(cookie)

# # Function to get the background color from the cookie
# def get_color_cookie():
#     cookie = Cookies.SimpleCookie(os.environ.get('HTTP_COOKIE'))
#     if 'bgcolor' in cookie:
#         return cookie['bgcolor'].value
#     return None

# # Get the background color from the cookie or use a default color
# bg_color = get_color_cookie() or '#FFFFFF'

# # Set the content type and print the HTTP header
# print('Content-Type: text/html')
# print()

# # Print the HTML page with the background color
# print(f'''
# <!DOCTYPE html>
# <html>
# <head>
#     <title>Colorful Page</title>
#     <style>
#         body {{
#             background-color: {bg_color};
#         }}
#     </style>
# </head>
# <body>
#     <h1>Welcome to the Colorful Page!</h1>
#     <p>This is a text page with a background color that you can change using cookies.</p>
#     <form method="POST">
#         <label for="color">Choose a color:</label>
#         <input type="color" id="color" name="color">
#         <input type="submit" value="Set Color">
#     </form>
# </body>
# </html>
# ''')

# # Process the form submission
# form = cgi.FieldStorage()
# if 'color' in form:
#     color = form['color'].value
#     set_color_cookie(color)
#!/usr/bin/python

# Import CGI and CGIT module
import cgi, cgitb

# to create instance of FieldStorage
# class which we can use to work
# with the submitted form data
form = cgi.FieldStorage()
your_name = form.getvalue('your_name')

# # to get the data from fields
company_name = form.getvalue('company_name')

print ("<html>")
print ("<head>")
print ("<title>First CGI Program</title>")
print ("</head>")
print ("<body>")
print ("<link rel=\"stylesheet\" href=\"./style.css\">")
print ("<div class=\"container\">")
print ("<a href=\"/\"><h1>WebServ</h1></a>")
print ("<p>CGI Python Test</p>")
print ("<h2>Hello, %s is working in %s</h2>"
	% (your_name, company_name))

print ("</body>")
print ("</html>")
