package robotics;

public class MobileBase {
    int numOfWheels;
    String LiDAR;
    boolean withCamera;
    Location location;
    public MobileBase(int numWheels, String LiDARType, boolean withCam, int initial_x, int initial_y) {
        numOfWheels = numWheels;
        LiDAR = LiDARType;
        withCamera = withCam;
        location = new Location(initial_x, initial_y);
    }

    public void MoveX(int dist) {
        location.SetX(location.GetX() + dist);
    }

    public void MoveY(int dist) {
        location.SetY(location.GetY() + dist);
    }

    public void ShowInfo() {
        System.out.println("**** Mobile base specs and status ****");
        System.out.println("Number of wheels: " + numOfWheels);
        System.out.println("LiDAR type: " + LiDAR);
        System.out.println("With Camera: " + withCamera);
        System.out.println("Current Location: (" + location.GetX() + ", " + location.GetY() + ")");
    }

    public Location GetLocation() {
        return location;
    }
}