from pynput.mouse import Button, Controller
import time

mouse = Controller()

def countdown():
    print("pressing button in 3...")
    time.sleep(1)
    print("                   2...")
    time.sleep(1)
    print("                   1...")
    time.sleep(1)
    return

while True:
    x = input("Press 1, 2 or 3 for left, right, or middle click: ")
    countdown()
    if x == "1":
        mouse.press(Button.left)
        time.sleep(1)
        mouse.release(Button.left)
    elif x == "2":
        mouse.press(Button.right)
        time.sleep(1)
        mouse.release(Button.right)
    elif x == "3":
        mouse.press(Button.middle)
        time.sleep(1)
        mouse.release(Button.middle)
