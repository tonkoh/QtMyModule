#ifndef MYXMLREADER_H
#define MYXMLREADER_H

#include <QXmlStreamReader>

class MyXmlReader : public QXmlStreamReader
{
public:
    MyXmlReader ();
    MyXmlReader ( QIODevice * device );
    MyXmlReader ( const QByteArray & data );
    MyXmlReader ( const QString & data );
    MyXmlReader ( const char * data );
    ~MyXmlReader();

    bool hasSourceSet(); //retruns true if this reader has a souce xml file set by setDevice method.
    bool skipToStartElement();
    bool nextSibling();
    bool skipTo(const QString &elemName, bool isDepthEqualityRequired);
};

#endif // MYXMLREADER_H
