from flic import flic

client = flic.Client()

class ButtonEventListener(flic.ButtonEventListener):

    def getHash(self):
        return "main"

    def onButtonUpOrDown(self, deviceId, queued, timeDiff, isUp, isDown):
        manager = client.getManager()
        button = manager.getButton(deviceId)
        print(button.getDeviceId() + (" up" if isUp else " down"))

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
