import webbrowser
import pytesseract
from PIL import Image
import os

def search_online(query):
    search_url = "https://scholar.google.com/scholar?q={}".format(query)   
    chrome_path = "C:/Program Files/Google/Chrome/Application/chrome.exe"  # Path to your Chrome executable

    # Open Chrome and perform the search
    webbrowser.register('chrome', None, webbrowser.BackgroundBrowser(chrome_path))
    webbrowser.get('chrome').open_new_tab(search_url)



# Get the path to the folder containing the files
folder_path = "./"  # Replace with the path to your folder

# Get the list of files in the folder
files = os.listdir(folder_path)

# Iterate over the files to find the image file
for file in files:
    file_path = os.path.join(folder_path, file)
    
    # Check if the file is an image
    if file.lower().endswith(('.png', '.jpg', '.jpeg', '.gif')):
        try:
            # Open the image file
            image = Image.open(file_path)

            # Apply OCR to the image and retrieve the text
            text = pytesseract.image_to_string(image)

            # Print or process the extracted text
            print(text)
            
            # Break the loop after processing the first image file
            break
        
        except OSError:
            print(f"Unable to process file: {file_path}")
    
if 'image' not in locals():
    print("No image file found in the folder.")

search_query = text
search_online(search_query)
# Delete the image file
os.remove(file_path)