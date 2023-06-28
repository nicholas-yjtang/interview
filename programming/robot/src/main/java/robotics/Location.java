package robotics;

public class Location {
    int x;
    int y;
    Location(int x, int y) {
        this.x = x;
        this.y = y;
    }
    int GetX() {
        return x;
    }   
    int GetY() {
        return y;
    }   
    void SetX(int x) {
        this.x = x;
    }
    void SetY(int y) {
        this.y = y;
    }
}
