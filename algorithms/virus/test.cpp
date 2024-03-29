#include <gtest/gtest.h>
#include <log4cxx/propertyconfigurator.h>
#include "transmission.h"
#include "WardFactory.h"

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

using namespace log4cxx;

TEST(TestVirus,TestVirus) {
    unique_ptr<Transmission> transmission = make_unique<Transmission> ();
    //example test case
    int ** patient_wards = new int*[3];
    patient_wards[0] = new int[5]{2,1,0,2,1};
    patient_wards[1] = new int[5]{1,1,1,1,1};
    patient_wards[2] = new int[5]{1,0,0,2,1};
    GTEST_ASSERT_EQ(transmission->getInfectedTime(3,5,patient_wards),2);
    WardFactory::free_wards(patient_wards, 3,5);
    //uninfected ward that is surrounded by empty beds
    patient_wards = new int*[5];
    patient_wards[0] = new int[5]{2,1,0,0,1};
    patient_wards[1] = new int[5]{1,1,1,0,0};
    patient_wards[2] = new int[5]{1,0,0,2,1};
    patient_wards[3] = new int[5]{1,0,0,2,1};
    patient_wards[4] = new int[5]{1,0,0,2,1};
    GTEST_ASSERT_EQ(transmission->getInfectedTime(5,5,patient_wards),-1);
    WardFactory::free_wards(patient_wards, 5,5);
    //only single uninfected patient
    patient_wards = new int*[1];
    patient_wards[0] = new int[1]{1};
    GTEST_ASSERT_EQ(transmission->getInfectedTime(1,1,patient_wards),-1);
    WardFactory::free_wards(patient_wards,1,1);
    //no infected patient
    patient_wards = new int*[5];
    patient_wards[0] = new int[5]{1,1,1,1,1};
    patient_wards[1] = new int[5]{1,1,1,0,0};
    patient_wards[2] = new int[5]{1,0,0,1,1};
    patient_wards[3] = new int[5]{1,0,0,1,1};
    patient_wards[4] = new int[5]{1,0,0,1,1};
    GTEST_ASSERT_EQ(transmission->getInfectedTime(5,5,patient_wards),-1);
    WardFactory::free_wards(patient_wards, 5,5);
    //all infected patient
    patient_wards = new int*[5];
    patient_wards[0] = new int[5]{2,2,2,2,2};
    patient_wards[1] = new int[5]{2,2,2,0,0};
    patient_wards[2] = new int[5]{2,0,0,2,2};
    patient_wards[3] = new int[5]{2,0,0,2,2};
    patient_wards[4] = new int[5]{2,0,0,2,2};    
    GTEST_ASSERT_EQ(transmission->getInfectedTime(5,5,patient_wards),0);
    WardFactory::free_wards(patient_wards, 5,5);
    //1 uninfected patient
    patient_wards = new int*[5];
    patient_wards[0] = new int[5]{2,2,2,2,2};
    patient_wards[1] = new int[5]{2,2,2,0,0};
    patient_wards[2] = new int[5]{2,0,0,2,2};
    patient_wards[3] = new int[5]{2,0,0,2,2};
    patient_wards[4] = new int[5]{2,0,0,1,2};    
    GTEST_ASSERT_EQ(transmission->getInfectedTime(5,5,patient_wards),1);
    WardFactory::free_wards(patient_wards, 5,5);
    //stress test with 1 infection at the top left corner
    patient_wards = WardFactory::create_ward(1000,1000);
    for (int i = 0; i < 1000; i++) {
      for (int j = 0; j < 1000; j++) {
        patient_wards[i][j] = 1;
      }
    }
    patient_wards[0][0] = 2;
    GTEST_ASSERT_EQ(transmission->getInfectedTime(1000,1000,patient_wards),1998);
    WardFactory::free_wards(patient_wards, 1000,1000);
    //stress test with all infections except for 1 at the bottom right
    patient_wards = WardFactory::create_ward(1000,1000);
    for (int i = 0; i < 1000; i++) {
      for (int j = 0; j < 1000; j++) {
        patient_wards[i][j] = 2;
      }
    }
    patient_wards[999][999] = 1;
    GTEST_ASSERT_EQ(transmission->getInfectedTime(1000,1000,patient_wards),1);
    WardFactory::free_wards(patient_wards, 1000,1000);
    //special case where the entire hospital is empty
    patient_wards = WardFactory::create_ward(1000,1000);
    for (int i = 0; i < 1000; i++) {
      for (int j = 0; j < 1000; j++) {
        patient_wards[i][j] = 0;
      }
    }
    GTEST_ASSERT_EQ(transmission->getInfectedTime(1000,1000,patient_wards),-1);
    WardFactory::free_wards(patient_wards, 1000,1000);

}

int main(int argc, char **argv) {
  PropertyConfigurator::configure("conf/log4j.properties");
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}