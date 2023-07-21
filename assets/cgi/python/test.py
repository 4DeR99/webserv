#!/usr/local/bin/python3
import cgi
import cgitb
import os
import sys

# Enable CGI error reporting
cgitb.enable()

cookies = {}

httpCookie = os.environ.get("HTTP_Cookie", None)
if  httpCookie:
    for cookie in httpCookie.split(";"):
        (key, value) = cookie.split("=")
        cookies[key.strip(" ")] = value

responseHeaders = []

name = cookies.get("name", "Unknown")
color = cookies.get("color", "white")

query = {}

httpQuery = os.environ.get("QUERY_STRING", None)
if httpQuery:
    for param in httpQuery.split("&"):
        (key, value) = param.split("=")
        query[key.strip(" ")] = value
    nameValue = query.get("name", None)
    if nameValue:
        responseHeaders += ["Set-Cookie: name=%s; Path=/" % nameValue]
        name = nameValue
    colorValue = query.get("color", None)
    if colorValue:
        responseHeaders += ["Set-Cookie: color=%s; Path=/" % colorValue]
        color = colorValue

options = ""

for i in ["white", "black", "red", "green", "yellow", "blue"]:
    options += "<option value=\"%s\" %s>%s</option>" % (i, "selected" if i == color else "", i.capitalize())


body = '''
<head>
    <title>CGI - Cookies </title>

    <style>
        * {
            background-color: %s;
        }
    </style>
</head>

<body>
    <h1>Welcome, %s</h1>
    <form action="/assets/cgi/python/test.py" method="GET">
        <input type="text" name="name" value="%s">
        <select name="color">
            %s
        </select>
        <input type="submit" value="Send">
    </form>
</body>

</html>
''' % (color, name, name, options)


print("Content-Length: %d" % len(body), end="\r\n")
print("Content-Type: text/html", end="\r\n")

for header in responseHeaders:
    print(header, end="\r\n")
print(end="\r\n")
print(body)