#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>

#include "main/helloworld.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

void Fun(const tutorial::HelloWorld& hello_world) {
    for(int i = 0; i<hello_world.msg_size(); i++)
    {
        const tutorial::TextMessage& tm = hello_world.msg(i);
        cout<<"Message ID: "<<tm.id()<<endl;
        cout<<"Message Title: "<<tm.title()<<endl;
        for(int j = 0; j < tm.dummy_size(); j++)
        {
            const tutorial::TextMessage::SubMessage& sm = tm.dummy(j);
            switch (sm.type())
            {
                case tutorial::TextMessage::URGENT:
                    cout<<"Urgent !"<<endl;
                    break;
                case tutorial::TextMessage::NORMAL:
                    cout<<"Normal !"<<endl;
                    break;
                default:
                    cout<<"Message type not specified."<<endl;
            }
            cout<<sm.subtext()<<endl;
        }
    
    }

  
}

int main(int argc, char* argv[]) {
  
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  tutorial::HelloWorld hello_world;
  {
    fstream input(argv[1], ios::in | ios::binary);
    if (!hello_world.ParseFromIstream(&input)) {
      cerr << "Failure in parsing" << endl;
      return -1;
    }
  }

  Fun(hello_world);

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
