#include "DSVReader.h"
#include "DSVWriter.h"
#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <vector>
#include "StringDataSource.h"
#include "StringDataSink.h"

//Reader tests
TEST(CDSVReaderTest, ReadSingleRow) {
    auto TestDataSource = std::make_shared<CStringDataSource>("A,B,C,D\n");
    CDSVReader reader(TestDataSource, ','); 
    std::vector<std::string> row;
    bool result = reader.ReadRow(row);

    EXPECT_TRUE(result);
    if(result == true){
        EXPECT_EQ(row.size(), 4u);
        EXPECT_EQ(row[0], "A");
        EXPECT_EQ(row[1], "B");
        EXPECT_EQ(row[2], "C");
        EXPECT_EQ(row[3], "D");
    }
}

TEST(CDSVReaderTest, ReadDiffDelimiter) {
    auto TestDataSource = std::make_shared<CStringDataSource>("item1|item2|item3\n");
    CDSVReader reader(TestDataSource, '|'); 
    std::vector<std::string> row;
    bool result = reader.ReadRow(row);

    EXPECT_TRUE(result);
    if(result == true){
        EXPECT_EQ(row.size(), 3u);
        EXPECT_EQ(row[0], "item1");
        EXPECT_EQ(row[1], "item2");
        EXPECT_EQ(row[2], "item3");
    }
}

TEST(CDSVReaderTest, ReadQuotes) {
    auto TestDataSource = std::make_shared<CStringDataSource>("\"hi, hi\",\"\"\"quote\"\"\",\"test\nTEST\"\n");
    CDSVReader reader(TestDataSource, ',');
    std::vector<std::string> row;
    bool result = reader.ReadRow(row);

    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(row.size(), 3u);
        EXPECT_EQ(row[0], "hi, hi");
        EXPECT_EQ(row[1], "\"quote\"");
        EXPECT_EQ(row[2], "test\nTEST");
    }
}

TEST(CDSVReaderTest, ReadEmpty) {
    auto TestDataSource = std::make_shared<CStringDataSource>(",,\n");
    CDSVReader reader(TestDataSource, ',');
    std::vector<std::string> row;
    bool result = reader.ReadRow(row);

    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(row.size(), 3u);
        for (const auto& field : row) {
            EXPECT_TRUE(field.empty());
        }
    }
}

TEST(CDSVReaderTest, ReadFromWriter) {
    std::string writtenData;
    {
        auto TestDataSink = std::make_shared<CStringDataSink>();
        CDSVWriter writer(TestDataSink, ',', false);
        std::vector<std::string> row = {"test1", "Test2", "test,test,test"};
        bool writeResult = writer.WriteRow(row);
        EXPECT_TRUE(writeResult);
        if (writeResult) {
            writtenData = TestDataSink->String();
        }
    }

    auto TestDataSource = std::make_shared<CStringDataSource>(writtenData);
    CDSVReader reader(TestDataSource, ',');
    std::vector<std::string> readRow;
    bool result = reader.ReadRow(readRow);

    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(readRow.size(), 3u);
        EXPECT_EQ(readRow[0], "test1");
        EXPECT_EQ(readRow[1], "Test2");
        EXPECT_EQ(readRow[2], "test,test,test");
    }
}


TEST(CDSVReaderTest, InnerDoubleQuote) {
    auto TestDataSource = std::make_shared<CStringDataSource>("\"hi\"\"hi\",hello\n");
    CDSVReader reader(TestDataSource, ',');
    std::vector<std::string> row;
    bool result = reader.ReadRow(row);

    EXPECT_TRUE(result);
    if (result) {
        EXPECT_EQ(row.size(), 2u);
        EXPECT_EQ(row[0], "hi\"hi");
        EXPECT_EQ(row[1], "hello");
    }
}

TEST(CDSVReaderTest, DelimiterAndEmpty) {
    auto TestDataSource = std::make_shared<CStringDataSource>(",x,\n,\n");
    CDSVReader reader(TestDataSource, ',');
    std::vector<std::string> row1, row2;
    reader.ReadRow(row1);
    reader.ReadRow(row2);

    EXPECT_EQ(row1.size(), 3);
    EXPECT_EQ(row1[1], "x");
    EXPECT_TRUE(row1[0].empty() && row1[2].empty());
    EXPECT_EQ(row2.size(), 2);
    EXPECT_TRUE(row2[0].empty());
}

TEST(CDSVReaderTest, EmptyLines) {
    auto TestDataSource = std::make_shared<CStringDataSource>("hi,hi,hi\n\n\nhi,hi,hi\n");
    CDSVReader reader(TestDataSource, ',');
    std::vector<std::string> row1, row2, row3, row4;
    reader.ReadRow(row1);
    reader.ReadRow(row2);
    reader.ReadRow(row3);
    reader.ReadRow(row4);
    
    EXPECT_EQ(row1.size(), 3u);
    EXPECT_EQ(row4.size(), 3u);
    EXPECT_EQ(row2.size(), 1u); // should be single emoty field ""
    EXPECT_EQ(row3.size(), 1u); //should be single emoty field ""
    EXPECT_TRUE(row2[0].empty() && row3[0].empty()); 

}

TEST(CDSVReaderTest, NotEndNewline) {
    auto TestDataSource = std::make_shared<CStringDataSource>("a,a,a\nb,b,q");
    CDSVReader reader(TestDataSource, ',');
    std::vector<std::string> row1, row2;
    reader.ReadRow(row1);
    bool result = reader.ReadRow(row2);

    EXPECT_TRUE(result);
    EXPECT_EQ(row2.size(), 3u);
    EXPECT_EQ(row2[0], "b");
    EXPECT_EQ(row2[1], "b");
    EXPECT_EQ(row2[2], "q");
}


//Writer tests
TEST(CDSVWriterTest, WriteSingleRow) {
    auto TestDataSink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(TestDataSink, ',', false);
    std::vector<std::string> row = {"W", "O", "R", "K"};
    bool result = writer.WriteRow(row); 

    EXPECT_TRUE(result);
    EXPECT_EQ(TestDataSink->String(), "W,O,R,K\n");
}

TEST(CDSVWriterTest, WriteEmptyFields) {
    auto TestDataSink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(TestDataSink, ',', false);
    std::vector<std::string> row = {"Hi", "", "Hello"};
    bool result = writer.WriteRow(row);

    EXPECT_TRUE(result);
    EXPECT_EQ(TestDataSink->String(), "Hi,,Hello\n");
}

TEST(CDSVWriterTest, WriteQuotes) {
    auto TestDataSink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(TestDataSink, ',', true);
    std::vector<std::string> row = {"\"Quotes\"", "hi,hello", "reg"};
    bool result = writer.WriteRow(row);

    EXPECT_TRUE(result);
    EXPECT_EQ(TestDataSink->String(), "\"\"\"Quotes\"\"\",\"hi,hello\",\"reg\"\n");
}

TEST(CDSVWriterTest, WriteAllEmpty) {
    auto TestDataSink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(TestDataSink, ',', false);
    std::vector<std::string> row = {"", "", ""};
    bool result = writer.WriteRow(row);

    EXPECT_TRUE(result);
    EXPECT_EQ(TestDataSink->String(), ",,\n");
}

TEST(CDSVWriterTest, WriteNewline) {
    auto TestDataSink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(TestDataSink, ',', true);
    std::vector<std::string> row = {"Line\nLine2", "test\nTest", "Three"};
    bool result = writer.WriteRow(row);

    EXPECT_TRUE(result);
    EXPECT_EQ(TestDataSink->String(), "\"Line\nLine2\",\"test\nTest\",\"Three\"\n");
}

TEST(CDSVWriterTest, WriteMultipleRows) {
    auto TestDataSink = std::make_shared<CStringDataSink>();
    CDSVWriter writer(TestDataSink, ',', false);
    std::vector<std::string> firstRow = {"A", "A", "A"};
    std::vector<std::string> secondRow = {"B", "B", "B"};
    bool firstResult = writer.WriteRow(firstRow);
    bool secondResult = writer.WriteRow(secondRow);

    EXPECT_TRUE(firstResult);
    EXPECT_TRUE(secondResult);
    EXPECT_EQ(TestDataSink->String(), "A,A,A\nB,B,B\n");
}
