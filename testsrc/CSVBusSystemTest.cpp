#include <gtest/gtest.h>
#include "CSVBusSystem.h"
#include "StringDataSource.h"
#include "BusSystem.h"

TEST(CSVBusSystem, SimpleExampleTest){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(),1);
    EXPECT_EQ(BusSystem.RouteCount(),0);
    EXPECT_EQ(BusSystem.StopByIndex(0)->ID(),1);
}

TEST(CSVBusSystem, BusSystemFuncsTest){
    auto InStreamStops2 = std::make_shared<CStringDataSource>("stop_id,node_id\n1,39283\n2,29333\n3,939282\n4,43924\n5,99999\n6,291");
    auto InStreamRoutes2 = std::make_shared<CStringDataSource>("route,stop_id\nA,39283\nA,29333\nA,939282\nB,43924\nB,99999\nB,291");
    auto CSVReaderStops2 = std::make_shared<CDSVReader>(InStreamStops2,',');
    auto CSVReaderRoutes2 = std::make_shared<CDSVReader>(InStreamRoutes2,',');
    CCSVBusSystem BusSystem2(CSVReaderStops2, CSVReaderRoutes2);

    //stop and route count
    EXPECT_EQ(BusSystem2.StopCount(), 6);
    EXPECT_EQ(BusSystem2.RouteCount(), 2);

    //STOPBYINDEX
    EXPECT_EQ(BusSystem2.StopByIndex(2)->ID(), 3);
    EXPECT_EQ(BusSystem2.StopByIndex(99), nullptr);

    //STOPBYID
    EXPECT_EQ(BusSystem2.StopByID(1)->ID(), 1);
    EXPECT_EQ(BusSystem2.StopByID(99), nullptr);

    //ROUTEBYINDEX
    EXPECT_EQ(BusSystem2.RouteByIndex(0)->Name(), "A");
    EXPECT_EQ(BusSystem2.RouteByIndex(99), nullptr);

    //ROUTEBYNAME
    EXPECT_EQ(BusSystem2.RouteByName("B")->Name(), "B");
    EXPECT_EQ(BusSystem2.RouteByName("D"), nullptr);
}

TEST(CSVBusSystem, StopAndRouteFuncsTest){
    auto InStreamStops3 = std::make_shared<CStringDataSource>("stop_id,node_id\n1,39283\n2,29333\n3,939282\n4,43924\n5,99999\n6,291");
    auto InStreamRoutes3 = std::make_shared<CStringDataSource>("route,stop_id\nA,39283\nA,29333\nA,939282\nB,43924\nB,99999\nB,291");
    auto CSVReaderStops3 = std::make_shared<CDSVReader>(InStreamStops3,',');
    auto CSVReaderRoutes3 = std::make_shared<CDSVReader>(InStreamRoutes3,',');
    CCSVBusSystem BusSystem3(CSVReaderStops3, CSVReaderRoutes3);

    //ID
    EXPECT_EQ(BusSystem3.StopByIndex(3)->ID(), 4);
    //NODEID
    EXPECT_EQ(BusSystem3.StopByIndex(2)->NodeID(), 939282);

    //NAME
    EXPECT_EQ(BusSystem3.RouteByIndex(1)->Name(), "B");
    //STOPCOUNT
    EXPECT_EQ(BusSystem3.RouteByIndex(1)->StopCount(), 3);
    //GETSTOPID
    EXPECT_EQ(BusSystem3.RouteByIndex(0)->GetStopID(2), 939282);
    EXPECT_EQ(BusSystem3.RouteByIndex(0)->GetStopID(99), std::numeric_limits<uint64_t>::max());


}
