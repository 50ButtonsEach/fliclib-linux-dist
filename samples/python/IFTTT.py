import requests
from flic import flic


makerkey = "Enter your key here"

client = flic.Client()

class ButtonEventListener(flic.ButtonEventListener):

    def getHash(self):
        return "main"

    def onButtonSingleOrDoubleClickOrHold(self, deviceId, queued, timeDiff, isSingleClick, isDoubleClick, isHold):
        manager = client.getManager()
        button = manager.getButton(deviceId)
        if isSingleClick :
           r = requests.post("https://maker.ifttt.com/trigger/FlicSingle/with/key/"+makerkey , json={})
           print r.status_code
        elif isDoubleClick :
           r = requests.post("https://maker.ifttt.com/trigger/FlicDouble/with/key/"+makerkey , json={})
           print r.status_code
        else :
           r = requests.post("https://maker.ifttt.com/trigger/FlicHold/with/key/"+makerkey , json={})
           print r.status_code

        
buttonEventListener = ButtonEventListener()

def addButtonEventListener(button):
    button.addButtonEventListener(buttonEventListener)

class ButtonListener(flic.ButtonListener):
    def getHash(self):
        return "main"

    def onButtonDiscover(self, button):
        addButtonEventListener(button)

buttonListener = ButtonListener()

class InitializedCallback(flic.CallbackVoid):
    def callback(self):
        print("Initialized")
        manager = client.getManager()
        buttons = manager.getButtons()
        try:
            for button in buttons:
                addButtonEventListener(button)
            manager.addButtonListener(buttonListener)
        except:
            pass

class UninitializedCallback(flic.CallbackBool):
    def callback(self):
        print("Uninitialized")


init = InitializedCallback()
uninit =  UninitializedCallback()
client.start(init.getCallback(), uninit.getCallback())

client.run()

