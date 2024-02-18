#include <gtest/gtest.h>
#include "OpenStreetMap.h"
#include "StringDataSource.h"
#include "StreetMap.h"

TEST(OpenStreetMap, SimpleExampleTest){
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
                                                        "<node id=\"1\" lat=\"1.0\" lon=\"-1.0\"/>"
                                                        "</osm>");
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);
    
    EXPECT_EQ(StreetMap.NodeCount(),1);
    EXPECT_EQ(StreetMap.WayCount(),0);
    EXPECT_EQ(StreetMap.NodeByIndex(0)->ID(),1);
}

TEST(OpenStreetMap, COpenStreetMapFuncsTest){
    auto InStream2 = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\"><node id=\"5727299821\" lat=\"38.5367699\" lon=\"-121.7698217\"/>"
	"<node id=\"5727299822\" lat=\"38.5368336\" lon=\"-121.7699747\"/>"
	"<node id=\"5754883274\" lat=\"38.5429559\" lon=\"-121.743289\"/>"
	"<node id=\"5754883277\" lat=\"38.5427743\" lon=\"-121.7432373\"/>"
	"<node id=\"5754883279\" lat=\"38.542878\" lon=\"-121.7431526\"/>"
	"<node id=\"5754883282\" lat=\"38.5430366\" lon=\"-121.7422949\"/>"
	"<way id=\"8699536\">"
		"<nd ref=\"258592863\"/>"
		"<nd ref=\"4399281377\"/>"
		"<nd ref=\"62224286\"/>"
		"<nd ref=\"62224288\"/>"
		"<nd ref=\"62224290\"/>"
		"<nd ref=\"62224293\"/>"
		"<nd ref=\"62224295\"/>"
		"<nd ref=\"62224297\"/>"
		"<nd ref=\"4399281328\"/>"
		"<nd ref=\"62224299\"/>"
		"<tag k=\"lanes\" v=\"2\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
		"<tag k=\"destination\" v=\"Sacramento\"/>"
		"<tag k=\"destination:ref\" v=\"I 80 East\"/>"
	"</way>"
	"<way id=\"8699555\">"
		"<nd ref=\"62224641\"/>"
		"<nd ref=\"4399280683\"/>"
		"<nd ref=\"62224643\"/>"
		"<nd ref=\"4399280686\"/>"
		"<nd ref=\"4399280688\"/>"
		"<nd ref=\"62224644\"/>"
		"<nd ref=\"62224645\"/>"
		"<nd ref=\"62224647\"/>"
		"<nd ref=\"4399281291\"/>"
		"<nd ref=\"4399281293\"/>"
		"<nd ref=\"62224649\"/>"
		"<nd ref=\"62224651\"/>"
		"<nd ref=\"62224653\"/>"
		"<nd ref=\"62224655\"/>"
		"<nd ref=\"62224658\"/>"
		"<nd ref=\"62224660\"/>"
		"<nd ref=\"4399281298\"/>"
		"<nd ref=\"62224661\"/>"
		"<nd ref=\"4399281302\"/>"
		"<nd ref=\"62224663\"/>"
		"<nd ref=\"62224666\"/>"
		"<nd ref=\"4399281310\"/>"
		"<nd ref=\"62224667\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"destination\" v=\"University of California Davis\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
		"<tag k=\"lanes\" v=\"1\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
	"</way>"
	"<way id=\"8700118\">"
		"<nd ref=\"62232638\"/>"
		"<nd ref=\"62232636\"/>"
		"<nd ref=\"62232634\"/>"
		"<nd ref=\"62232633\"/>"
		"<tag k=\"lanes\" v=\"2\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
	"</way>");
    
    auto Reader2 = std::make_shared<CXMLReader>(InStream2);
    COpenStreetMap StreetMap2(Reader2);

    //NODE AND WAY COUNT
    EXPECT_EQ(StreetMap2.NodeCount(), 6);
    EXPECT_EQ(StreetMap2.WayCount(), 3);

    //NODEBYINDEX
    EXPECT_EQ(StreetMap2.NodeByIndex(3)->ID(), 5754883277);
    EXPECT_EQ(StreetMap2.NodeByIndex(22), nullptr);

    //NODEBYID
    EXPECT_EQ(StreetMap2.NodeByID(5754883282)->ID(), 5754883282);
    EXPECT_EQ(StreetMap2.NodeByID(2), nullptr);

    //WAYBYINDEX
    EXPECT_EQ(StreetMap2.WayByIndex(0)->ID(), 8699536);
    EXPECT_EQ(StreetMap2.WayByIndex(19), nullptr);

    //WAYBYID
    EXPECT_EQ(StreetMap2.WayByID(8700118)->ID(), 8700118);
    EXPECT_EQ(StreetMap2.WayByID(22222), nullptr);


}

TEST(OpenStreetMap, NodeFuncsTest){
    auto InStream3 = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\"><node id=\"5727299821\" lat=\"38.5367699\" lon=\"-121.7698217\"/>"
	"<node id=\"5727299822\" lat=\"38.5368336\" lon=\"-121.7699747\"/>"
	"<node id=\"5754883274\" lat=\"38.5429559\" lon=\"-121.743289\"/>"
	"<node id=\"5754883277\" lat=\"38.5427743\" lon=\"-121.7432373\"/>"
	"<node id=\"5754883279\" lat=\"38.542878\" lon=\"-121.7431526\"/>"
	"<node id=\"5754883282\" lat=\"38.5430366\" lon=\"-121.7422949\"/>"
    "<node id=\"5603341990\" lat=\"38.5579708\" lon=\"-121.6757518\">"
		"<tag k=\"highway\" v=\"stop\"/>"
	"</node>"
	"<way id=\"8699536\">"
		"<nd ref=\"258592863\"/>"
		"<nd ref=\"4399281377\"/>"
		"<nd ref=\"62224286\"/>"
		"<nd ref=\"62224288\"/>"
		"<nd ref=\"62224290\"/>"
		"<nd ref=\"62224293\"/>"
		"<nd ref=\"62224295\"/>"
		"<nd ref=\"62224297\"/>"
		"<nd ref=\"4399281328\"/>"
		"<nd ref=\"62224299\"/>"
		"<tag k=\"lanes\" v=\"2\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
		"<tag k=\"destination\" v=\"Sacramento\"/>"
		"<tag k=\"destination:ref\" v=\"I 80 East\"/>"
	"</way>"
	"<way id=\"8699555\">"
		"<nd ref=\"62224641\"/>"
		"<nd ref=\"4399280683\"/>"
		"<nd ref=\"62224643\"/>"
		"<nd ref=\"4399280686\"/>"
		"<nd ref=\"4399280688\"/>"
		"<nd ref=\"62224644\"/>"
		"<nd ref=\"62224645\"/>"
		"<nd ref=\"62224647\"/>"
		"<nd ref=\"4399281291\"/>"
		"<nd ref=\"4399281293\"/>"
		"<nd ref=\"62224649\"/>"
		"<nd ref=\"62224651\"/>"
		"<nd ref=\"62224653\"/>"
		"<nd ref=\"62224655\"/>"
		"<nd ref=\"62224658\"/>"
		"<nd ref=\"62224660\"/>"
		"<nd ref=\"4399281298\"/>"
		"<nd ref=\"62224661\"/>"
		"<nd ref=\"4399281302\"/>"
		"<nd ref=\"62224663\"/>"
		"<nd ref=\"62224666\"/>"
		"<nd ref=\"4399281310\"/>"
		"<nd ref=\"62224667\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"destination\" v=\"University of California Davis\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
		"<tag k=\"lanes\" v=\"1\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
	"</way>"
	"<way id=\"8700118\">"
		"<nd ref=\"62232638\"/>"
		"<nd ref=\"62232636\"/>"
		"<nd ref=\"62232634\"/>"
		"<nd ref=\"62232633\"/>"
		"<tag k=\"lanes\" v=\"2\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
	"</way>");
    
    auto Reader3 = std::make_shared<CXMLReader>(InStream3);
    COpenStreetMap StreetMap3(Reader3);

    //NODE FUNCS
    //ID
    EXPECT_EQ(StreetMap3.NodeByIndex(0)->ID(), 5727299821);

    //LOCATION
    EXPECT_EQ(StreetMap3.NodeByIndex(0)->Location(), std::make_pair(38.5367699, -121.7698217));

    //ATTRIBUTECOUNT
    EXPECT_EQ(StreetMap3.NodeByIndex(0)->AttributeCount(), 0);
    EXPECT_EQ(StreetMap3.NodeByIndex(6)->AttributeCount(), 1);

    //GETATTRIBUTEKEY
    EXPECT_EQ(StreetMap3.NodeByIndex(6)->GetAttributeKey(0), "highway");
    EXPECT_EQ(StreetMap3.NodeByIndex(0)->GetAttributeKey(1), "");

    //HASATTRIBUTE
    EXPECT_EQ(StreetMap3.NodeByIndex(0)->HasAttribute("Test"), false);
    EXPECT_EQ(StreetMap3.NodeByIndex(6)->HasAttribute("highway"), true);

    //GETATTRIBUTE
    EXPECT_EQ(StreetMap3.NodeByIndex(6)->GetAttribute("highway"), "stop");
    EXPECT_EQ(StreetMap3.NodeByIndex(6)->GetAttribute("doesnt exist"), "");

}

TEST(OpenStreetMap, WayFuncsTest){
    auto InStream4 = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">""<way id=\"8699536\">"
		"<nd ref=\"258592863\"/>"
		"<nd ref=\"4399281377\"/>"
		"<nd ref=\"62224286\"/>"
		"<nd ref=\"62224288\"/>"
		"<nd ref=\"62224290\"/>"
		"<nd ref=\"62224293\"/>"
		"<nd ref=\"62224295\"/>"
		"<nd ref=\"62224297\"/>"
		"<nd ref=\"4399281328\"/>"
		"<nd ref=\"62224299\"/>"
		"<tag k=\"lanes\" v=\"2\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
		"<tag k=\"destination\" v=\"Sacramento\"/>"
		"<tag k=\"destination:ref\" v=\"I 80 East\"/>"
	"</way>"
	"<way id=\"8699555\">"
		"<nd ref=\"62224641\"/>"
		"<nd ref=\"4399280683\"/>"
		"<nd ref=\"62224643\"/>"
		"<nd ref=\"4399280686\"/>"
		"<nd ref=\"4399280688\"/>"
		"<nd ref=\"62224644\"/>"
		"<nd ref=\"62224645\"/>"
		"<nd ref=\"62224647\"/>"
		"<nd ref=\"4399281291\"/>"
		"<nd ref=\"4399281293\"/>"
		"<nd ref=\"62224649\"/>"
		"<nd ref=\"62224651\"/>"
		"<nd ref=\"62224653\"/>"
		"<nd ref=\"62224655\"/>"
		"<nd ref=\"62224658\"/>"
		"<nd ref=\"62224660\"/>"
		"<nd ref=\"4399281298\"/>"
		"<nd ref=\"62224661\"/>"
		"<nd ref=\"4399281302\"/>"
		"<nd ref=\"62224663\"/>"
		"<nd ref=\"62224666\"/>"
		"<nd ref=\"4399281310\"/>"
		"<nd ref=\"62224667\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"destination\" v=\"University of California Davis\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
		"<tag k=\"lanes\" v=\"1\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
	"</way>"
	"<way id=\"8700118\">"
		"<nd ref=\"62232638\"/>"
		"<nd ref=\"62232636\"/>"
		"<nd ref=\"62232634\"/>"
		"<nd ref=\"62232633\"/>"
		"<tag k=\"lanes\" v=\"2\"/>"
		"<tag k=\"oneway\" v=\"yes\"/>"
		"<tag k=\"bicycle\" v=\"no\"/>"
		"<tag k=\"highway\" v=\"motorway_link\"/>"
	"</way>");

    auto Reader4 = std::make_shared<CXMLReader>(InStream4);
    COpenStreetMap StreetMap4(Reader4);

    //ID
    EXPECT_EQ(StreetMap4.WayByIndex(0)->ID(), 8699536);
    
    //NODECOUNT
    EXPECT_EQ(StreetMap4.WayByIndex(0)->NodeCount(), 10);

    //GETNODEID
    EXPECT_EQ(StreetMap4.WayByIndex(1)->GetNodeID(3), 4399280686);
    EXPECT_EQ(StreetMap4.WayByIndex(1)->GetNodeID(9999), std::numeric_limits<uint64_t>::max());

    //ATTRIBUTECOUNT
    EXPECT_EQ(StreetMap4.WayByIndex(1)->AttributeCount(), 5);

    //GETATTRIBUTEKEY
    EXPECT_EQ(StreetMap4.WayByIndex(2)->GetAttributeKey(3), "highway");
    EXPECT_EQ(StreetMap4.WayByIndex(2)->GetAttributeKey(999), "");

    //HASATTRIBUTE
    EXPECT_EQ(StreetMap4.WayByIndex(2)->HasAttribute("lanes"), true);
    EXPECT_EQ(StreetMap4.WayByIndex(2)->HasAttribute("nonexistant"), false);

    //GETATTRIBUTE
    EXPECT_EQ(StreetMap4.WayByIndex(2)->GetAttribute("bicycle"), "no");
    EXPECT_EQ(StreetMap4.WayByIndex(2)->GetAttribute("fake"), "");
}


