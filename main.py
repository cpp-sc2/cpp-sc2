
# Import external libraries
# import pyttsx3 # A text-to-speech library I plan to play around with later on
# import pytesseract # A library which can help us with retrieving in-game screen info
# import pyautogui # Some extra GUI tools we could use
import tkinter as tk
import subprocess
import time


# Function to check if StarCraft 2 is running
def isStarCraftRunning():
    process_list = subprocess.Popen(["tasklist"], stdout=subprocess.PIPE, text=True)
    output = process_list.communicate()[0]
    return any("SC2" in line or "StarCraft" in line for line in output.splitlines())


# Create a function to update the GUI
def updateGui(window, canvas):
    if isStarCraftRunning():
        canvas.itemconfig("status_message", text="StarCraft II is running!")
        window.after(100, updateGui, window, canvas)  # Check every 1/2 second
    else:
        canvas.itemconfig("status_message", text="Closing StarCraft II...")
        window.after(3000, window.destroy)
        print("Your StarCraft II session has ended.")


# Main entry code
def main():
    # Print to console that overlay has begun
    print("StarCraft II Overlay has started.")
    
    # Create the main window
    window = tk.Tk()
    window.title("StarCraft 2 Overlay")

    # Create a black canvas
    canvas = tk.Canvas(window, width=400, height=100, bg="black")
    canvas.pack()

    # Add the message to the canvas
    message = canvas.create_text(
        200,
        50,
        text="Started StarCraft 2",
        fill="white",
        font=("Helvetica", 16),
        anchor="center",
        tags="status_message"  # Use the correct tag
    )

    # Center the window on the screen
    window.update_idletasks()
    screen_width = window.winfo_screenwidth()
    screen_height = window.winfo_screenheight()
    window_width = window.winfo_width()
    window_height = window.winfo_height()
    x = (screen_width - window_width) // 2
    y = (screen_height - window_height) // 2
    window.geometry(f"{window_width}x{window_height}+{x}+{y}")

    # Start checking if StarCraft 2 is running
    updateGui(window, canvas)

    # Run the GUI main loop
    window.mainloop()


# Run the program
if __name__ == "__main__":
    main()
