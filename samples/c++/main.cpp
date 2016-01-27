#include <iostream>

#include "flic.hpp"

void log(const std::string& message) {
    std::cout << message << std::endl;
}

void errlog(const std::string& message) {
    std::cout << message << std::endl;
}

class LogManagerListener : public flic::client::manager::ManagerListener {
    virtual void onBluetoothStateChange(const bool& state) {
	log("Bluetooth state changed: " + std::to_string(state));
    }

    virtual void onScanningStarted() {
	log("Scanning started");
    }

    virtual void onScanningStopped() {
	log("Scanning stopped");
    }
};

class LogButtonEventListener : public flic::client::button::ButtonEventListener {
public:
    virtual std::string getHash() override {
	return "LogButtonEventListener";
    }

    virtual void onConnecting(const std::string& deviceId) override {
	log("Connecting to: " + deviceId);
    }

    virtual void onConnect(const std::string& deviceId) override {
	log("Connected to: " + deviceId);
    }

    virtual void onReady(const std::string& deviceId) override {
	log("Verified: " + deviceId);
    }

    virtual void onDisconnecting(const std::string& deviceId) override {
	log("Disconnecting from: " + deviceId);
    }

    virtual void onDisconnect(const std::string& deviceId) override {
	log("Disconnected from: " + deviceId);
    }

    virtual void onConnectionFail(const std::string& deviceId) override {
	log("Connection failed to: " + deviceId);
    }

    virtual void onButtonUpOrDown(const std::string& deviceId,
				  const bool& queued,
				  const int& timeDiff,
				  const bool& isUp,
				  const bool& isDown) override {
	log("Button " + std::string(isUp ? "up" : "down") + " (up/down): " + deviceId);
    }

    virtual void onButtonClickOrHold(const std::string& deviceId,
				     const bool& queued,
				     const int& timeDiff,
				     const bool& isClick,
				     const bool& isHold) override {
	log("Button " + std::string(isClick ? "click" : "hold") + " (click/hold): " + deviceId);
    }

    virtual void onButtonSingleOrDoubleClick(const std::string& deviceId,
					     const bool& queued,
					     const int& timeDiff,
					     const bool& isSingleClick,
					     const bool& isDoubleClick) override {
	log("Button " + std::string(isSingleClick ? "single click" : "double click") + " (single/double): " + deviceId);
    }

    virtual void onButtonSingleOrDoubleClickOrHold(const std::string& deviceId,
						   const bool& queued,
						   const int& timeDiff,
						   const bool& isSingleClick,
						   const bool& isDoubleClick,
						   const bool& isHold) override {
	log("Button " + std::string(isSingleClick ? "single click" : isDoubleClick ? "double click" : "hold") + " (single/double/hold): " + deviceId);
    }

    virtual void onBatteryStatus(const std::string& deviceId,
				 const int& battery) override {
	log("Button battery status: " + deviceId);
    }

    virtual void onRssiValue(const std::string& deviceId,
			     const int& rssi) override {
	log("Button rssi value: " + deviceId);
    }
};

class LogButtonListener : public flic::client::manager::ButtonListener {
private:
    std::shared_ptr<flic::client::manager::Manager> manager;
public:
    LogButtonListener(std::shared_ptr<flic::client::manager::Manager> manager) :
	manager(manager) {

    }

    virtual std::string getHash() override {
	return "LogButtonListener";
    }

    virtual void onButtonDiscover(const std::string& deviceId) override {
	log("Button discovered: " + deviceId);
	auto button = manager->getButton(deviceId);
	button->addButtonEventListener(std::shared_ptr<flic::client::button::ButtonEventListener>(new LogButtonEventListener()));
    }

    virtual void onButtonForgotten(const std::string& deviceId) override {
	log("Button forgotten: " + deviceId);
    }
};

int main() {
    flic::client::Client client;

    try {
	client.start([&client] () {
		auto manager = client.getManager();

		manager->addButtonListener(std::shared_ptr<flic::client::manager::ButtonListener>(new LogButtonListener(manager)));

		for (auto& button : manager->getButtons()) {
		    button->addButtonEventListener(std::shared_ptr<flic::client::button::ButtonEventListener>(new LogButtonEventListener()));
		}
	    }, [&client] (const bool& resumable) {

	    });
	client.run();
    } catch (flic::client::ClientNetworkException& e) {
	errlog(e.what());
    } catch (std::exception& e) {
	errlog(e.what());
    } catch (...) {
	errlog("Unknown exception");
    }
}
