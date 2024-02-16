#include "XMLReader.h"
#include "XMLWriter.h"
#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <vector>
#include "StringDataSource.h"
#include "StringDataSink.h"


TEST(XMLWriterTest, WriteStart) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "container", {{"ID", "A"}}}));
    Writer.Flush();
    EXPECT_EQ(OutputStream->String(), "<container ID=\"A\">");
}

TEST(XMLWriterTest, WriteAttributes) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CompleteElement, "hi", {{"lang", "en"}}}));
    Writer.Flush();

    EXPECT_EQ(OutputStream->String(), "<hi lang=\"en\"/>");
}

TEST(XMLWriterTest, WriteEnd) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    Writer.WriteEntity({SXMLEntity::EType::StartElement, "container", {}});
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "container", {}}));
    Writer.Flush();

    EXPECT_EQ(OutputStream->String(), "<container></container>");
}

TEST(XMLWriterTest, WriteCharacter) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "hi, hello", {}}));
    Writer.Flush();
    EXPECT_EQ(OutputStream->String(), "hi, hello");
}

TEST(XMLWriterTest, WriteNested) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    Writer.WriteEntity({SXMLEntity::EType::StartElement, "test", {}});
    Writer.WriteEntity({SXMLEntity::EType::CompleteElement, "TEST", {{"category", "dog"}}});
    Writer.WriteEntity({SXMLEntity::EType::CharData, "test test", {}});
    Writer.WriteEntity({SXMLEntity::EType::EndElement, "test", {}}); 
    Writer.Flush();

    EXPECT_EQ(OutputStream->String(), "<test><TEST category=\"dog\"/>test test</test>"); 
}

TEST(XMLWriterTest, WriteSpecialCharacters) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CompleteElement, "test", {{"test", "\"<&'>\""}}}));
    Writer.Flush();
    EXPECT_EQ(OutputStream->String(), "<test test=\"&quot;&lt;&amp;&apos;&gt;&quot;\"/>");

}

TEST(XMLWriterTest, WriteEmpty) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CompleteElement, "nothing", {}}));
    Writer.Flush();
    EXPECT_EQ(OutputStream->String(), "<nothing/>");
}

TEST(XMLWriterTest, WriteWhitespace) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "    testing space    "}));
    Writer.Flush();
    EXPECT_EQ(OutputStream->String(), "    testing space    ");
}

TEST(XMLWriterTest, WriteMultipleAttributes) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CompleteElement, "test", {{"ID", "1111"}, {"type", "test"}, {"woo", "ah"}}}));
    Writer.Flush();
    EXPECT_EQ(OutputStream->String(), "<test ID=\"1111\" type=\"test\" woo=\"ah\"/>");
}

//Reader Tests
TEST(XMLReaderTest, ReadStartAndEnd) {
    auto InputStream = std::make_shared<CStringDataSource>("<test>hello</test>");
    CXMLReader Reader(InputStream);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity, false)); //start
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "test");

    EXPECT_TRUE(Reader.ReadEntity(Entity, false)); // char data
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);
    EXPECT_EQ(Entity.DNameData, "hello");

    EXPECT_TRUE(Reader.ReadEntity(Entity, false)); //end
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "test");
}

TEST(XMLReaderTest, ReadNested) {
    auto InputStream = std::make_shared<CStringDataSource>(
        "<test><TEST>hi</TEST></test>");
    CXMLReader Reader(InputStream);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "test");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "TEST");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);
    EXPECT_EQ(Entity.DNameData, "hi");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "TEST");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "test");
}

TEST(XMLReaderTest, ReadSimple) {
    auto InputStream = std::make_shared<CStringDataSource>("<test>TEST</test>");
    CXMLReader Reader(InputStream);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "test");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);
    EXPECT_EQ(Entity.DNameData, "TEST");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "test");
}


TEST(XMLReaderTest, SkipCharData) {
    auto InputStream = std::make_shared<CStringDataSource>("<hi>blah blah</hi>");
    CXMLReader Reader(InputStream);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity, true)); // Pass true to skip char data
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "hi");
    EXPECT_TRUE(Reader.ReadEntity(Entity, true));  //skip blah blah
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "hi");
}


TEST(XMLReaderTest, ReadAttr) {
    auto InputStream = std::make_shared<CStringDataSource>("<test test=\"a\" hi=\"test\"></test>");
    CXMLReader Reader(InputStream);
    SXMLEntity entity;

    EXPECT_TRUE(Reader.ReadEntity(entity));
    EXPECT_EQ(entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_TRUE(entity.AttributeExists("test"));
    EXPECT_EQ(entity.AttributeValue("test"), "a");
    EXPECT_TRUE(entity.AttributeExists("hi"));
    EXPECT_EQ(entity.AttributeValue("hi"), "test");
}

TEST(XMLReaderWriterTest, ReadWriter) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);//use xml writer
    Writer.WriteEntity({SXMLEntity::EType::StartElement, "test", {{"idk", "d"}}});
    Writer.WriteEntity({SXMLEntity::EType::CharData, "hi"});
    Writer.WriteEntity({SXMLEntity::EType::EndElement, "test"});

    auto InputStream = std::make_shared<CStringDataSource>(OutputStream->String()); // read from writer
    CXMLReader Reader(InputStream);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity, false));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "test");
    EXPECT_EQ(Entity.AttributeValue("idk"), "d");

    EXPECT_TRUE(Reader.ReadEntity(Entity, false));//char data
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);
    EXPECT_EQ(Entity.DNameData, "hi");

    EXPECT_TRUE(Reader.ReadEntity(Entity, false));//test end
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(Entity.DNameData, "test");
}
