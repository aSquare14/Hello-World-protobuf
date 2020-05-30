// See README.txt for information and build instructions.

#include <ctime>
#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>

#include "main/helloworld.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

void Fun(tutorial::TextMessage* textmsg) {
    cout<<"Enter message ID: ";
    int id; cin>>id;
    textmsg->set_id(id);
    cin.ignore(256,'\n');

    cout << "Enter title: ";
    getline(cin, *textmsg->mutable_title());
    
    while (true) {
        cout << "Enter a SubMessage: ";
        string subtext;
        getline(cin, subtext);
        if (subtext.empty()) {
        break;
        }
        tutorial::TextMessage::SubMessage* simple_message = textmsg->add_dummy();
       simple_message->set_subtext(subtext);

        cout << "Is this urgent? ";
        string type;
        getline(cin, type);
        if (type == "yes") {
        simple_message->set_type(tutorial::TextMessage::URGENT);
        } else if (type == "no") {
        simple_message->set_type(tutorial::TextMessage::NORMAL);
        } else {
        cout << "Unknown message type. Using default" << endl;
        }
    }
}

int main(int argc, char* argv[]) {

  GOOGLE_PROTOBUF_VERIFY_VERSION;
  
  tutorial::HelloWorld hello_world;
  
  Fun(hello_world.add_msg());
  {
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!hello_world.SerializeToOstream(&output)) {
      cerr << "Failed to write Hello World Object" << endl;
      return -1;
    }
  }

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
