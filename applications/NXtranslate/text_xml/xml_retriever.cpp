#include <algorithm>
#include <iostream>
#include <fstream>
#include <libxml/xmlmemory.h>
#include <stdexcept>
#include <string>
#include <vector>
#include "retriever.h"
#include "xml_retriever_dom.h"
#include "../node.h"
#include "../node_util.h"
#include "../string_util.h"
#include "../tree.hh"

using std::ifstream;
using std::invalid_argument;
using std::runtime_error;
using std::string;
using std::cout;
using std::endl;
using std::vector;
using string_util::starts_with;

typedef vector<string>     StringVec;
typedef tree<Node>         NodeTree;
typedef NodeTree::iterator NodeTreeIter;

static string get_type(const string &location){
  static const string CHAR("CHAR");
  if(starts_with(location,CHAR))
    return "NX_CHAR";

  static const string INT8("INT8");
  if(starts_with(location,INT8))
    return "NX_INT8";

  static const string INT16("INT16");
  if(starts_with(location,INT16))
    return "NX_INT16";

  static const string INT32("INT32");
  if(starts_with(location,INT32))
    return "NX_INT32";

  static const string UINT8("UINT8");
  if(starts_with(location,UINT8))
    return "NX_UINT8";

  static const string UINT16("UINT16");
  if(starts_with(location,UINT16))
    return "NX_UINT16";

  static const string UINT32("UINT32");
  if(starts_with(location,UINT32))
    return "NX_UINT32";

  static const string FLOAT32("FLOAT32");
  if(starts_with(location,FLOAT32))
    return "NX_FLOAT32";

  static const string FLOAT64("FLOAT64");
  if(starts_with(location,FLOAT64))
    return "NX_FLOAT64";

  throw invalid_argument("Cannot determine type in location: "+location);
}

static string xmlChar_to_str(const xmlChar *ch, int len){
  string result((char *)ch);
  if( (len>0) && ((unsigned int)len<result.size()) )
    result.erase(result.begin()+len,result.end());

  return string_util::trim(result);
}

static bool is_right_square_bracket(const char c){
  static const string RIGHT="]";
  return find(RIGHT.begin(),RIGHT.end(),c)!=RIGHT.end();
}

static string get_dims(const string &location){
  using std::find;
  static const string LEFT("[");

  if(!starts_with(location,LEFT))
    return "";

  string result="";
  for(string::const_iterator it=location.begin() ; it!=location.end() ; it++ ){
    result+=(*it);
    if(is_right_square_bracket(*it))
      break;
  }

  if(result.size()==location.size())
    return "";
  else
    return result;
}

/**
 * The factory will call the constructor with a string. The string
 * specifies where to locate the data (e.g. a filename), but
 * interpreting the string is left up to the implementing code.
 */
TextXmlRetriever::TextXmlRetriever(const string &str): source(str), __tree(new tree<Node>){

  // fill tree
  string warn=buildTree(str,*__tree);

  // check that the document is not empty
  if(__tree->size()<=0)
    throw runtime_error("Empty document ["+source+"]");
}

TextXmlRetriever::~TextXmlRetriever(){
  //cout << "~TextXmlRetriever()" << endl;
  
  // __tree does not need to be deleted
}

static Node getNode(Ptr<NodeTree> tr, const StringVec &path){
  // set up iterators for dealing with the path
  StringVec::const_iterator path_it=path.begin();
  StringVec::const_iterator path_end=path.end();
  
  for( NodeTreeIter it=tr->begin() ; it!=tr->end() ;  ){
    if(it->name()==(*path_it)){
      path_it++;
      if(path_it==path_end)
        return *it;
      it=tr->child(it,0);
    }else{
      it=tr->next_sibling(it);
    }
  }

  // when the code gets here the path was not found
  string error;
  for( StringVec::const_iterator it=path.begin() ; it!=path_end ; it++ )
    error+="/"+(*it);
  throw runtime_error("PATH["+error+"] NOT FOUND IN FILE");
}

/**
 * This is the method for retrieving data from a file. The whole
 * tree will be written to the new file immediately after being
 * called. Interpreting the string is left up to the implementing
 * code.
 */
void TextXmlRetriever::getData(const string &location, tree<Node> &tr){
  //  cout << "TextXmlRetriever::getData(" << location << ",tree)" << endl; // REMOVE
  // check that the argument is not an empty string
  if(location.size()<=0)
    throw invalid_argument("cannot parse empty string");

  // variables for the divided string version of the location
  string str_path;
  string type;
  string str_dims;

  // convert the location to a type and (string) path
  if(starts_with(location,"/")){
    str_path=location;
    type="NX_CHAR";
    str_dims="";
  }else{
    // get the type and remove it from the location
    type=get_type(location);
    str_path=location.substr(type.size()-3,location.size());
    // get the dimensions and remove it from the location
    str_dims=get_dims(str_path);
    str_path=str_path.substr(str_dims.size(),str_path.size());
    // remove the separating colon
    str_path=str_path.substr(1,str_path.size());
  }
  //std::cout << "TYPE=" << type << " DIMS=" << str_dims << " PATH=" << str_path << std::endl; // REMOVE

  StringVec path=string_util::string_to_path(str_path);
  Node::NXtype int_type=node_type(type);
  Node node=getNode(__tree,path);

/* OLD
  // put the data in the node
  vector<int> dims;
  if(int_type==Node::CHAR){
    dims.push_back(value.size());
  }else{
    dims=string_util::str_to_intVec(str_dims);
  }

  update_node_from_string(node,value,dims,int_type);
*/

  // put the node in the supplied tree to pass it back
  tr.insert(tr.begin(),node);
}

const string TextXmlRetriever::MIME_TYPE("text/xml");

string TextXmlRetriever::toString() const{
  return "["+MIME_TYPE+"] "+source;
}
