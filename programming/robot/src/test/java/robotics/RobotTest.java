package robotics;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

/**
 * Unit test for simple App.
 */
public class RobotTest 
    extends TestCase
{
    /**
     * Create the test case
     *
     * @param testName name of the test case
     */
    public RobotTest( String testName )
    {
        super( testName );
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite()
    {
        return new TestSuite( RobotTest.class );
    }

    /**
     * Rigourous Test :-)
     */
    public void testRobot()
    {
        String serialString = "20220518A01";
        String LiDARString = "Husarion ROSbot 2 Pro";
        Robot robot = new Robot(serialString, 4, LiDARString, true, 0, 0);
        robot.ShowManufacturer();
        robot.ShowSerialNo();
        System.out.println("");
        robot.ShowNumberofRobotsExisting();
        
        Location location = robot.base.GetLocation();
        System.out.println("Initial Location: (" + location.GetX() + ", " + location.GetY() + ")");

        robot.base.MoveX(30);
        robot.base.MoveY(-50);
        robot.base.ShowInfo();

        robot = new Robot("20220518B03", 2, "TurtleBot Waffle Pi", false, 30, 0);
        robot.ShowManufacturer();
        robot.ShowSerialNo();
        System.out.println("");
        robot.ShowNumberofRobotsExisting();

        robot.base.MoveX(200);
        robot.base.MoveY(-100);
        robot.base.ShowInfo();
    }

}
