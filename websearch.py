import webbrowser
import pytesseract
from PIL import Image

def search_online(query):
    search_url = "https://scholar.google.com/scholar?q={}".format(query)   
    chrome_path = "C:/Program Files/Google/Chrome/Application/chrome.exe"  # Path to your Chrome executable

    # Open Chrome and perform the search
    webbrowser.register('chrome', None, webbrowser.BackgroundBrowser(chrome_path))
    webbrowser.get('chrome').open_new_tab(search_url)


image_path = "b.png"  # Replace with the path to your image file
image = Image.open(image_path)

# Apply OCR to the image and retrieve the text
text = pytesseract.image_to_string(image)
# Example usage
search_query = text
search_online(search_query)