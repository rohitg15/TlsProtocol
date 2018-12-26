#include "record.h"
#include "testrecord.h"
#include <vector>


RecordTest::RecordTest()
{
};

RecordTest::~RecordTest()
{
};

void RecordTest::SetUp()
{
};

void RecordTest::TearDown()
{
};

TEST_F(RecordTest, ProtocolVersionSizeAligned)
{
    tls::ProtocolVersion version;
    version.major = 0x1;
    version.minor = 0x2;
    ASSERT_EQ(sizeof(version), sizeof(version.major) + sizeof(version.minor));
    ASSERT_EQ(sizeof(tls::ProtocolVersion), 2);
}

TEST_F(RecordTest, TlsMessageZeroFragmentSizeAligned)
{   
    size_t expSize = 0;
    expSize += sizeof(tls::TlsMessage::type);
    expSize += sizeof(tls::TlsMessage::version);
    expSize += sizeof(tls::TlsMessage::length);
    expSize += sizeof(tls::TlsMessage::fragment);

    ASSERT_EQ(expSize, sizeof(tls::TlsMessage));
}

TEST_F(RecordTest, TlsMessageFragmentSizeAligned)
{
    // allocate a buffer to hold the packet
    // we want say 8 bytes of packet fragment
    uint16_t length = 8;
    size_t expSize = sizeof(tls::TlsMessage);
    expSize += (length * sizeof(uint8_t));

    std::vector<uint8_t> buf(expSize, 0);
    tls::TlsMessage *pTlsRecord = 
        reinterpret_cast<tls::TlsMessage*>(buf.data());
    pTlsRecord->type = tls::ContentType::Handshake;
    pTlsRecord->length = length;


    for(int i = 0; i < length; ++i)
    {
        ASSERT_NO_THROW(pTlsRecord->fragment[i] = static_cast<uint8_t>(1));
    }
}