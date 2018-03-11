#ifndef RUBBERDUCKYDETECTOR_HPP
#define RUBBERDUCKYDETECTOR_HPP

#include <QDialog>
#include <QtConcurrent>

namespace Ui {
class RubberDuckyDetector;
}

class RubberDuckyDetector : public QDialog
{
    Q_OBJECT

public:
    explicit RubberDuckyDetector(QWidget *parent = 0);
    ~RubberDuckyDetector();
public slots:
    /**
     * @brief checkPresenceOfKeyStrokeInjector This method is actually used to detect the presence
     * of malicious devices like rubber ducky. [RUN THIS SLOT AS A SEPERATE THREAD]
     */
    void checkPresenceOfKeyStrokeInjector();
    /**
     * @brief informKeystrokeInjector This slot will inform the user that the keystroke injector has
     * been inserted.
     */
    void informKeystrokeInjector();
    /**
     * @brief informUSBDrive This method is used to inform the presence of USB device
     */
    void informUSBDrive();
signals:
    /**
     * @brief driveIsKeyStrokeInjector This signal will be emitted if the connected
     * input drive is actually a KeyStroke injector
     */
    void driveIsKeyStrokeInjector();
    /**
     * @brief driveIsUSB This method will check if the drive is a USB device or not.
     */
    void driveIsUSB();

private:
    Ui::RubberDuckyDetector *ui;

    // Initial no of USB drives present in the computer
    volatile int initial_usbDrivesCount = 0;
    // Initial no of Input devices present in the computer
    volatile int initial_inputDevicesCount = 0;
    // A thread to check for the keystroke injector
    QFuture<void> checkForKeyStrokeInjectoThread;
    // The state of the thread [RUNNING/TERMINATED]
    volatile bool running = true;
    // Private method declarations

    /**
     * @brief getCountOfUSBDevices This method will get the total no of usb drives present in the system
     * @returns the total no of usb drives
     */
    int getCountOfUSBDevices();
    /**
     * @brief getCountOfInputDevices This method will be useful to get the count of input devices
     * @return count of input devices
     */
    int getCountOfInputDevices();

};

#endif // RUBBERDUCKYDETECTOR_HPP
