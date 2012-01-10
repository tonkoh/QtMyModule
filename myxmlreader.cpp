#include "myxmlreader.h"

MyXmlReader::MyXmlReader():QXmlStreamReader()
{
}

MyXmlReader::MyXmlReader(QIODevice * device ):
        QXmlStreamReader(device )
{
}

MyXmlReader::MyXmlReader(const QByteArray & data):
        QXmlStreamReader(data)
{
}

MyXmlReader::MyXmlReader(const QString & data):
        QXmlStreamReader(data)
{
}

MyXmlReader::MyXmlReader(const char * data):
        QXmlStreamReader(data)
{
}

MyXmlReader::~MyXmlReader()
{
}

bool MyXmlReader::hasSourceSet()
{
    return device() != 0;
}

//skipToStartElement skips parse process to a next start element within a
//following XML document.
bool MyXmlReader::skipToStartElement()
{
    Q_ASSERT(hasSourceSet());

    while(readNext() != QXmlStreamReader::EndDocument){
        if(tokenType() == QXmlStreamReader::StartElement)
            return true;
    }
    return false;
}

bool MyXmlReader::nextSibling()
{
    Q_ASSERT(hasSourceSet());

    int depth = 0;
    int prevTokenType = tokenType();

    while(readNext() != QXmlStreamReader::EndDocument){
        if(tokenType() == QXmlStreamReader::StartElement){
            if(prevTokenType == QXmlStreamReader::StartElement)
                depth += 1;
            else if(depth == 0){
                return true;
            }
        }else if(tokenType() == QXmlStreamReader::EndElement){
            if(prevTokenType == QXmlStreamReader::EndElement)
                depth -= 1;
        }else if(tokenType() == QXmlStreamReader::Characters){
            isWhitespace();
            continue;
        }

        prevTokenType = tokenType();
    }
    return false;
}


bool MyXmlReader::skipTo(const QString &elemName, bool isDepthEqualityRequired)
{
    Q_ASSERT(hasSourceSet());

    if(isDepthEqualityRequired){
        while(nextSibling()){
            if(name() == elemName)
                return true;
        }
    }else{
        while(skipToStartElement()){
            if(name() == elemName)
                return true;
        }
    }

    return false;
}
