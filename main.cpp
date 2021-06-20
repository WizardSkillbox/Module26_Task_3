#include <iostream>
#include <string>
#include <map>

using namespace std;

class Window{
    int width;
    int height;

public:
    Window(int width, int height) {
        this->width = width;
        this->height = height;
    }

    void resize(int dX, int dY) {
        width += dX;
        height += dY;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

};

class Monitor{
    static const int kWidth = 80;
    static const int kHeight = 50;

    int leftX = 0;
    int leftY = 0;

    Window * currentWindow = nullptr;

    static int getIntFromStream(const string &message, int min, int max = INT32_MAX) {
        int64_t num;
        bool isCorrect = false;
        while (!isCorrect) {
            cout << message << " (" << min << " - " << max << ") :";
            isCorrect = !!(cin >> num) && (num >= min && num <= max);
            if (!isCorrect) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error! Please enter a number, which is from " << min << " to " << max << "!" << endl;
            }
        }
        return (int) num;
    }

public:
    ~Monitor() {
            delete currentWindow;
    }

    void createWindow() {
        leftX = getIntFromStream("Enter X coord of left corner of a new window", 0, kWidth);
        leftY = getIntFromStream("Enter Y coord of left corner of a new window", 0, kHeight);
        int width = getIntFromStream("Enter width of a new window", 0);
        int height = getIntFromStream("Enter height of a new window", 0);

        delete currentWindow;

        currentWindow = new Window(width, height);
    }

    void moveWindow() {
        if(currentWindow == nullptr) {
            cout << "Error! The monitor has not any active window!" << endl;
            return;
        }

        leftX +=  getIntFromStream("Enter dX", -leftX, kWidth - leftX);
        leftY +=  getIntFromStream("Enter dY", -leftY, kHeight - leftY);

        cout << " Window has moved: X = " << leftX << ", Y = " << leftY << endl;
    }

    void resizeWindow() {
        if(currentWindow == nullptr) {
            cout << "Error! The monitor has not any active window!" << endl;
            return;
        }

       int newWidth = getIntFromStream("Enter new width", 0);
       int newHeight = getIntFromStream("Enter height", 0);
       currentWindow->resize(newWidth - currentWindow->getWidth(), newHeight - currentWindow->getHeight());
       cout << " Window has resized: Width = " << currentWindow->getWidth() << ", Height = " << currentWindow->getHeight() << endl;
    }

    void display() {
        for (int i = 0; i < kHeight; ++i) {
            for (int j = 0; j < kWidth; ++j) {
                if(nullptr != currentWindow && i >= leftX && i < leftX + currentWindow->getHeight() && j >= leftY && j < leftY + currentWindow->getWidth()) {
                    cout << '1';
                } else {
                    cout << '0';
                }
            }
            cout << endl;
        }
    }
};

int main() {
    string cmd;

    auto monitor = new Monitor();
    monitor->createWindow();

    while (true) {
        cout << "Enter command (move|resize|display|close): " << endl;
        cin >> cmd;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (cmd == "move") {
            monitor->moveWindow();
        } else if (cmd == "resize") {
            monitor->resizeWindow();
        } else if (cmd == "display") {
            monitor->display();
        } else if (cmd == "close") {
            break;
        } else {
            cout << "Error. Incorrect command" << endl;
        }
    }
    delete monitor;
}

