//#include "jsonP_parser.h"
//#include "jsonP_buffer_parser.h"
#include "jsonP_push_parser.h"
#include "net_chunk_impl.h"
//#include "IPush_handler.h"
#include "modified_json_push_handler_impl.h"

#include <iostream>
#include <iomanip>
//#include <fstream>
#include <stdio.h>
#include <chrono>


typedef std::chrono::high_resolution_clock clock2;
typedef std::chrono::duration<float, std::milli> mil;

void populate_object(element_object *);
void print_object(element_object *);
void parse_file(std::string, std::string &);

int main(int argc, char **argv)
{
	// sample how to parse json text as array/object
	std::cout << "**********************************************************\n\n";
	std::cout << "sample how to parse json text as array/object...\n";
	std::string t{"{\n  \"key1\" : null, \n  \"key2\" : +35.544e4, \n  \"key3\" : 12345.321e+2, \n  \"obj\" : { \n    \"k1\" : \"v1\", \n  \"k2\" : \"v2\" \n  },\n  \"found\" : \"found value\", \n  \"arr\": [ null,\"ak1\" ,true, \"ak_val1\" ] \n }"};
	std::string t2{"[{\"key1\" : null, \"key2\" : +35.544e4, \"key3\" : \"string value\", \"small_array\" : [true, false, true]}, {\"key1\" : null, \"key2\" : -452.544e-2, \"key3\" : \"string value2\", \"small_array\" : [true, false, false]}]"};
	
	element *doc_root = nullptr;
	jsonP_doc *doc = nullptr;
	
	try {
		jsonP_parser doc_parser{};
		doc = doc_parser.parse(t);			//json text of type object
//		doc = parser.parse(t2);		//json text of type array

		std::string s;
		std::string s2;

		std::cout << std::boolalpha;
		std::cout << "Doc Type: " << doc->get_type() << std::endl;

		if (doc->get_type() == object) {
			doc_root = doc->get_object();
		} else if (doc->get_type() == array) {
			doc_root = doc->get_array();
		}
		
		doc_root->stringify(s);					//compact print
		doc_root->stringify_pretty(s2);			//pretty print
		
		std::cout << "\n*** stringify ***\n" << s << std::endl;
		std::cout << "\n*** pretty  ***\n" << s2 << std::endl;
		
		delete doc;
		delete doc_root;

	} catch (jsonP_exception &ex) {
		std::cout << "parse exception caught: " << ex.what() << std::endl;
		delete doc;
		delete doc_root;
	}
	
	
	
	
	//sample of creating json object and accessing its elements
	std::cout << "**********************************************************\n\n";
	std::cout << "sample of creating json object and accessing its elements...\n";
	element_object *e_object = nullptr;
	try {
		e_object = new element_object{};
		populate_object(e_object);
		print_object(e_object);
		
		std::string s;
		e_object->stringify_pretty(s);
		std::cout << "\n*** pretty stringify ***\n" << s << std::endl;
		delete e_object;
	} catch (jsonP_exception &ex) {
		std::cout << "json exception caught: " << ex.what() << std::endl;
		delete e_object;
	}
	
	
	
	//sample parsing json text files
	std::cout << "**********************************************************\n\n";
	std::cout << "sample parsing json file using the nonbuffer parser, the whole file is loaded into memory first...\n";
	jsonP_doc *parse_doc = nullptr;
	element_object *parse_object = nullptr;
		
	try {
		std::string json_pretty;
		
		{
			std::cout << "\n\n*** opening text file ***\n";
			std::string json;
//			parse_file("/Users/user1/Downloads/large.json", json);
			parse_file("../samples/webapp.json", json);
			std::cout << "*** parsing text file with jsonP ***\n";

			long l0 = clock2::now().time_since_epoch().count();
			auto t0 = clock2::now();

			jsonP_parser parser{json};
			parse_doc = parser.parse();

			long l1 = clock2::now().time_since_epoch().count();
			auto t1 = clock2::now();
			std::cout << "DONE parsing, elapsed time: " << (l1-l0) << ", " << mil(t1-t0).count() << "ms\n";
		}
		
		parse_object = parse_doc->get_object();
		std::cout << "*** calling pretty stringify ***\n";
		parse_object->stringify_pretty(json_pretty);
		
		delete parse_doc;
		delete parse_object;
		
		std::cout << "*** contents of json ***\n";
		std::cout << json_pretty << std::endl;
	} catch (jsonP_exception &ex) {
		std::cout << "Parse exception parsing text file: " << ex.what() << std::endl;
		delete parse_doc;
		delete parse_object;
	}



	// sample parsing json file using the buffer parser
	std::cout << "**********************************************************\n\n";
	std::cout << "sample parsing json file using the buffer parser...\n";
//	jsonP_buffer_parser buf_parser{"/Users/user1/Downloads/large.json", 8192};
	jsonP_buffer_parser *buf_parser = new jsonP_buffer_parser{"../samples/webapp.json", 1000};
	auto buf_t0 = clock2::now();
	jsonP_doc *doc_buf = buf_parser->parse();
	auto buf_t1 = clock2::now();
	std::string buf_s;
	element_object *buf_obj = doc_buf->get_object();
	buf_obj->stringify_pretty(buf_s);
	std::cout << "\n" << buf_s << "\n";

	std::cout << "buffer parser parse time: " << mil(buf_t1-buf_t0).count() << "/ms" << std::endl;
	
	delete buf_obj;
	delete doc_buf;
	delete buf_parser;
	
	
	
	// sample streaming json from the net by implementing a custom IChunk_reader interface and supplying it to the buffer parser
//	std::cout << "\n**********************************************************\n\n";
//	std::cout << "Starting buffer_parser test with IChunk_reader implementation net_chunk_impl\n";
//	net_chunk_impl *net_reader = new net_chunk_impl{};
//	jsonP_buffer_parser *net_buf_parser = new jsonP_buffer_parser{net_reader, 8192};
//	jsonP_doc *doc_net_buf = net_buf_parser->parse();
//	std::string net_buf_s;
//	element_object *net_buf_obj = doc_net_buf->get_object();
//	net_buf_obj->stringify_pretty(net_buf_s);
//	std::cout << "\n\n" << doc_net_buf->get_type() << "\n\n";
//	std::cout << net_buf_s << std::endl;
//	
//	delete net_buf_obj;
//	delete doc_net_buf;
//	delete net_buf_parser;



	// sample streaming json from the net by implementing a custom IChunk_reader interface and supplying it to the buffer parser
	// and using a push handler to create a compact json object of only keys being looked for
	std::cout << "\n**********************************************************\n\n";
	std::cout << "Starting buffer_parser test with IChunk_reader implementation net_chunk_impl and the the modified_json_push_handler_impl\n";
	net_chunk_impl *net_reader2 = new net_chunk_impl{};
	modified_json_push_handler_impl *handler_net_push = new modified_json_push_handler_impl{object};
	handler_net_push->add_key("/meta/view", "metadata");
	jsonP_push_parser *net_push_parser = new jsonP_push_parser{net_reader2, handler_net_push, 8192};
	net_push_parser->parse();
	element *net_push_handler_element = handler_net_push->get_modified_json();
	std::string net_push_handler_s;
	net_push_handler_element->stringify_pretty(net_push_handler_s);
	std::cout << "\n*** Modified Json ***\n" << net_push_handler_s << std::endl;
	
	delete net_push_handler_element;
	delete handler_net_push;
	delete net_push_parser;
	/* jsonP_push_parser owns the IChunk_reader instance, and it will delete it when the parser is deleted */



	// sample using the IPush_handler implementation test_push_handler
	std::cout << "\n**********************************************************\n\n";
	std::cout << "Starting push_parser test with IPush_handler implementation test_push_handler\n";
	IPush_handler *handler = new test_push_handler{};
	jsonP_push_parser *push_parser = new jsonP_push_parser{"../samples/sample2.json", handler};
//	jsonP_push_parser *push_parser = new jsonP_push_parser{"/Users/user1/Downloads/large.json", handler};
	auto push_buf_t0 = clock2::now();
	push_parser->parse();
	auto push_buf_t1 = clock2::now();
	
	std::cout << "Done Parsing with push_parser, parse time: " << mil(push_buf_t1-push_buf_t0).count() << "/ms" << std::endl;
	delete push_parser;
	delete handler;



	// sample using the IPush_handler implementation modified_json_push_handler_impl
	std::cout << "\n**********************************************************\n\n";
	std::cout << "Starting push_parser test with the modified_json_push_handler_impl\n";
	modified_json_push_handler_impl *handler2 = new modified_json_push_handler_impl{object};
//	handler2->add_key("/glossary/GlossDiv/GlossList/GlossEntry", "GlossDef");
//	handler2->add_key("glossary/GlossDiv/", "title");
	handler2->add_key("/meta/view", "tableAuthor");
	handler2->add_key("/meta/view/query", "orderBys");
	handler2->debug_key_map();
	jsonP_push_parser *push_parser2 = new jsonP_push_parser{"../samples/sample5.json", handler2};
	auto push_buf2_t0 = clock2::now();
	push_parser2->parse();
	auto push_buf2_t1 = clock2::now();
	std::cout << "Done Parsing with push_parser, parse time: " << mil(push_buf2_t1-push_buf2_t0).count() << "/ms" << std::endl;
	element *push_handler_element = handler2->get_modified_json();
	std::string push_handler_s;
	push_handler_element->stringify_pretty(push_handler_s);
	std::cout << "\n" << push_handler_s << std::endl;
	
	delete push_handler_element;
	delete handler2;
	delete push_parser2;
 
	return 0;
}



void populate_object(element_object *doc)
{
	doc->add_element("key1", new element_string{"string1"});
	doc->add_element("key2", new element_numeric(long(98989898)));
	doc->add_element("key3", new element_boolean{true});
	doc->add_element("key3.5", new element_numeric(12345.1233e1));
	
	element_array *arr = new element_array{string};
	arr->add_element(new element_string{"val1"});
	arr->add_element(new element_string{"val2"});
	arr->add_element(new element_string{"val3"});
	
	doc->add_element("key4", arr);
	
	element_object *obj_a = new element_object{};
	obj_a->add_element("sub-1", new element_boolean{true});
	obj_a->add_element("sub-2", new element_numeric{-9892333});
	
	element_object *obj_b = new element_object{};
	obj_b->add_element("sub-A1", new element_boolean{false});
	obj_b->add_element("sub-A2", new element_string{"somehing"});
	obj_b->add_element("sub-doc", obj_a);
	
	element_array *arr2 = new element_array{object};
	arr2->add_element(obj_b);
	arr2->add_element(obj_b);
	arr2->add_element(obj_b);
	
	doc->add_element("key5", obj_b);//arr2);
	
	element_object *obj = new element_object{};
	obj->add_element("sub1", new element_boolean{true});
	obj->add_element("sub2", new element_boolean{false});
	obj->add_element("sub3", new element_boolean{true});
	
	doc->add_element("key6", obj);
	
}

void print_object(element_object *doc)
{
	try {
		std::cout << "\n\n*** print object ***\n";
		std::cout << "key1: " << doc->get_as_string("key1") << std::endl;
		std::cout << "key2: " << doc->get_as_numeric_long("key2") << std::endl;
		std::cout << "key3: " << doc->get_as_boolean("key3") << std::endl;
		std::cout << "key3.5: " << doc->get_as_numeric_double("key3.5") << std::endl;
		
		std::vector<element*> v = doc->get_as_array("key4");
		std::cout << "elements of array with key4:" << std::endl;
		for (element *e : v)
			std::cout << e->get_string_value() << std::endl;
			
		element_object *obj = doc->get_as_object("key6");
		std::cout << "bools of embedded object with key6\n";
		std::cout << "sub1: " << obj->get_as_boolean("sub1") << std::endl;
		std::cout << "sub2: " << obj->get_as_boolean("sub2") << std::endl;
		std::cout << "sub3: " << obj->get_as_boolean("sub3") << std::endl;
	
	} catch (const char *error) { std::cout << "Error: " << error << std::endl; }
}


void parse_file(std::string f, std::string &json)
{
//	std::ifstream in_file{f};
	std::string line;
	
//	if (!in_file) {
//		std::cerr << "File failed to open" << std::endl;
//		return;
//	}
//	
//	while (std::getline(in_file, line))
//		json += line;
		
	
	FILE *fp = std::fopen(f.c_str(), "r");
	
	if (fp == NULL) {
		std::cerr << "File failed to open" << std::endl;
		return;
	}
	
	char buf[4096];
	
	while (fread((void *)buf, sizeof(char), 4095, fp) > 0) {
		json += buf;
	}
	
	fclose(fp);
	
	std::cout << f << ", file size: " << json.length() << std::endl;
}