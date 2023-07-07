package robotics;

public class Robot {
    private static String robotManufacturer = "Robotics Inc.";
    private static int numberofRobotsExisting = 0;
    private String serialNumber;
    public MobileBase base;
    public Robot(String serial, int numwheels, String LiDARType, boolean withCam, int initial_x, int initial_y) {
        serialNumber = serial;
        base = new MobileBase(numwheels, LiDARType, withCam, initial_x, initial_y);
        numberofRobotsExisting++;
    }

    public void ShowManufacturer() {
        System.out.println("Manufacturer is: " + robotManufacturer);        
    }

    public void ShowSerialNo() {
        System.out.println("Serial number is: " + serialNumber);        
    }

    public void ShowNumberofRobotsExisting() {
        System.out.println("Number of robots existing is: " + numberofRobotsExisting);        
    }
}
