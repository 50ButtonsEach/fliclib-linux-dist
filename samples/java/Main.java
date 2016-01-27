import io.flic.lib.client.*;

public class Main {
    private static void addButtonEventListener(Button button) {
	button.addButtonEventListener(new ButtonEventListener() {
		@Override
		public void onButtonUpOrDown(String deviceId,
					     boolean queued,
					     int timeDiff,
					     boolean isUp,
					     boolean isDown) {
		    System.out.println(deviceId + (isUp ? " up" : " down"));
		}
	    });
    }

    public static void main(String [] args) {
	System.load("/usr/lib/libflicjava.so");
	final Client client = new Client();

	CallbackVoid initializedCallback = new CallbackVoid() {
		public void callback() {
		    System.out.println("Initialized");
		    final Manager manager = client.getManager();
		    try {
			ButtonVector buttons = manager.getButtons();
			for (int i = 0; i < buttons.size(); ++i) {
			    Button button = buttons.get(i);
			    addButtonEventListener(button);
			}
			manager.addButtonListener(new ButtonListener() {
				@Override
				public String getHash() {
				    return "main";
				}

				@Override
				public void onButtonDiscover(String deviceId) {
				    Button button = manager.getButton(deviceId);
				    addButtonEventListener(button);
				}

				@Override
				public void onButtonForgotten(String deviceId) {
				    System.out.println("onButtonForgotten");
				}
			    });
		    } catch (Exception e) {
			System.out.println(e);
		    }
		}
	    };
	CallbackBool uninitializedCallback = new CallbackBool() {
		public void callback() {
		    System.out.println("Uninitialized");
		}
	    };
	System.out.println("start");
	client.start(initializedCallback.getCallback(),
		     uninitializedCallback.getCallback());
	client.run();
    }
}
