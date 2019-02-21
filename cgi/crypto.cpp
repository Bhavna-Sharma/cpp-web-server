#include <iostream>

#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>

int main( int, char** )
{
    /*CryptoPP::SHA256 hash;

    std::string text = "elan";
    std::string digest = "";

    hash.Transform(digest, text.data());

    std::cout << "i: " << digest << std::endl;

    return 0;*/

    using namespace CryptoPP;
HexEncoder encoder(new FileSink(std::cout));

std::string msg = "Yoda said, Do or do not. There is no try.";
std::string digest;

SHA1 hash;
hash.Update((const byte*)msg.data(), msg.size());
digest.resize(hash.DigestSize());
hash.Final((byte*)&digest[0]);

std::cout << "Message: " << msg << std::endl;

std::cout << "Digest: ";
StringSource(digest, true, new Redirector(encoder));
std::cout << std::endl;
}
