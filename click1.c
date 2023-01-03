#include <QApplication>
#include <QPushButton>
#include <QSerialPort>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create a push button with the text "Click me"
    QPushButton button("Click me");

    // Connect the button's clicked signal to a lambda function
    QObject::connect(&button, &QPushButton::clicked, [&] {
        static bool on = false;  // toggle state

        // Open the serial port COM1
        QSerialPort serial;
        serial.setPortName("COM1");
        if (serial.open(QIODevice::WriteOnly)) {
            // Write an "on" or "off" message to the serial port
            serial.write(on ? "on\n" : "off\n");
            serial.close();
        }

        // Toggle the state
        on = !on;
    });

    button.show();
    return app.exec();
}
