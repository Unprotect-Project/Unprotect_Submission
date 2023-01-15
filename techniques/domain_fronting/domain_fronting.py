import requests
import re

# The actual destination domain requested
destination_domain = "www.youtube.com"

# The fronting domain used in ssl
fronting_domain = "www.google.com"

# Create a session object
session = requests.Session()

# force real destination in the Host header
session.headers["Host"] = destination_domain

# Send the request to the fronting domain
response = session.get("https://" + fronting_domain, headers={'X-Originating-URL': 'https://' + destination_domain})

# Extract the title of the received page
title = re.search("<title>(.*)</title>", response.text)
print(title.group(1))
