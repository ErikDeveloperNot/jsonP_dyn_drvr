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
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
//#include "rapidjson/error/en.h"

//#include "sajson.h"


typedef std::chrono::high_resolution_clock clock2;
typedef std::chrono::duration<float, std::milli> mil;

jsonP_json * create_json_doc();
//void print_object(element_object *);
char * parse_file(std::string, std::string &);

int main(int argc, char **argv)
{

	
	//sample of creating json object and accessing its elements
	std::cout << "\n\n**********************************************************\n";
	std::cout << "sample of creating json object and accessing its elements...\n";
	
	jsonP_json *json = nullptr;
	
	try {
		json = create_json_doc();
		char *pretty_json = json->stringify_pretty();
		std::cout << "json after creation:\n" << pretty_json << "\n";
		free(pretty_json);
		
		error err;
		search_path_element paths[3];
		char p3[] = {"O-new_obj_key-O-new_obj_key_embed-A-3"};
		char delim3[] = {"-"};

		if (json->build_search_path(p3, delim3, paths) != 0) {
			std::cout << "**** ERROR building search path *****" << std::endl;
		}

		std::cout << "\n ---- Deleting ---- \n";

		if (json->delete_value(paths, 3, NULL, &err) != 0) {
			std::cout << "**** ERROR deleting, error code: " << err << std::endl;
		} else {
			pretty_json = json->stringify_pretty();
			std::cout << "json after delete:\n" << pretty_json << "\n";
			free(pretty_json);
		}
		
		char p4[] = {"O-new_obj_key-O-new_obj_key_embed"};

		if (json->build_search_path(p4, delim3, paths) != 0) {
			std::cout << "**** ERROR building search path *****" << std::endl;
		}
		\
		unsigned int member_cnt = json->get_elements_count(paths, 2);
		std::cout << "\nmembers count: " << member_cnt << std::endl;

		//sample getting object keys using the object_id
		object_id test_id = json->get_object_id(paths, 1);
		struct object_key *obj_keys;
		unsigned int k_cnt = json->get_keys(test_id, obj_keys);
		std::cout << "Number of Keys: " << k_cnt << std::endl;
		
		for (unsigned int i=0; i<k_cnt; i++) {
			std::cout << "type: " << obj_keys[i].type << ", key: " << obj_keys[i].key << std::endl;
		}

		free(obj_keys);

		//sample getting object keys using search_path_element
//		k_cnt = json->get_keys(paths, 1, obj_keys);
//		std::cout << "Number of Keys: " << k_cnt << std::endl;
//
//		for (unsigned int i=0; i<k_cnt; i++) {
//			std::cout << "type: " << obj_keys[i].type << ", key: " << obj_keys[i].key << std::endl;
//		}
//
//		free(obj_keys);

		//print contents of array using get_next_array_element. the first call takes an object_id or search_path_element
		// each call after takes 0 instead of the object_id. An empty element_type is returned when no more elements
		char p5[] = {"O-string_array\0"};
		json->build_search_path(p5, delim3, paths);
		const void *v;

		element_type t_arry = json->get_next_array_element(paths, 1, v);
		std::cout << "\nType returned: " << get_element_type_string(t_arry) << std::endl;
		std::cout << "Value returned: " << (char*)v << std::endl;
		t_arry = json->get_next_array_element(0, v);
		std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
		std::cout << "Value returned: " << std::endl;
		t_arry = json->get_next_array_element(0, v);
		std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
		std::cout << "Value returned: " << *(long*)v << std::endl;
		t_arry = json->get_next_array_element(0, v);
		std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
		std::cout << "Value returned: " << *(double*)v << std::endl;
		t_arry = json->get_next_array_element(0, v);
		std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
		t_arry = json->get_next_array_element(0, v);
		std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
		t_arry = json->get_next_array_element(0, v);
		std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
		std::cout << "Element count: " << json->get_elements_count(*(object_id*)v) << std::endl;
		t_arry = json->get_next_array_element(0, v);
		std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
		std::cout << "Element count: " << json->get_members_count(*(object_id*)v) << std::endl;
		t_arry = json->get_next_array_element(0, v);
		std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
		
		char new_obj_key[] = {"new_obj_key\0"};
		char double_key[] = {"double_key\0"};
		char long_key[] = {"long_key\0"};
		char bool_t_key[] = {"bool_t_key\0"};
		char NEW_KEY[] = {"NEW_KEY\0"};
		
		paths[0].type = object_key;
		paths[0].key = new_obj_key;
		
		//get simple value types
		paths[1].type = object_key;
		paths[1].key = double_key;
		std::cout << "\ndouble value: " << json->get_double_value(paths, 2, &err) << std::endl; 
		paths[1].type = object_key;
		paths[1].key = long_key;
		std::cout << "long value: " << json->get_long_value(paths, 2, &err) << std::endl;
		paths[1].type = object_key;
		paths[1].key = bool_t_key;
		std::cout << "bool value: " << json->get_bool_value(paths, 2, &err) << std::endl; 
		paths[1].type = object_key;
		paths[1].key = NEW_KEY;
		std::cout << "string value: " << json->get_string_value(paths, 2, &err) << std::endl; 
		
		//update value
		char string_v[] = {"new string value\0"};
		json->update_value(paths, 2, string, string_v);
		std::cout << "updated string value: " << json->get_string_value(paths, 2, &err) << std::endl; 
		
		delete json;
	} catch (jsonP_exception &ex) {
		std::cout << "json exception caught: " << ex.what() << std::endl;
		delete json;
	}
	
	
	
	//sample parsing json text files
	std::cout << "\n\n**********************************************************\n";
	std::cout << "sample parsing json file using the nonbuffer parser, the whole file is loaded into memory first...\n";
	jsonP_json *parse_doc = nullptr;

	try {
		std::string json_pretty;
		std::cout << "\n*** opening text file ***\n";
		std::string json;
//			char *json2 = parse_file("/Users/user1/Downloads/large.json", json);
//			char *json2 = parse_file("../samples/webapp2.json", json);
		char *json2 = parse_file("../samples/sample1.json.t", json);
//			char *json2 = parse_file("../samples/med.json", json);
		std::cout << "*** parsing text file with jsonP ***\n" << std::endl;
		auto t0 = clock2::now();

		jsonP_parser parser{json2, (unsigned int)strlen(json2), /*DONT_SORT_KEYS*/};
		parse_doc = parser.parse();
		auto t1 = clock2::now();

		std::cout << "\nDONE parsing, elapsed time: " << mil(t1-t0).count() << "ms\n" << std::endl;
			
		parse_stats stats = parser.get_parse_stats();
		std::cout << "Parse stats, data increases: " << stats.data_increases << ", stack buffer increases: " << stats.stack_buf_increases << std::endl;
		t0 = clock2::now();
		char *stringify = parse_doc->stringify();		
		t1 = clock2::now();
		std::cout << "\nDONE stringify, elapsed time: " << mil(t1-t0).count() << "ms\n" << std::endl;
		std::cout << stringify << std::endl;
		free(stringify);
		t0 = clock2::now();
		char *stringify_pretty = parse_doc->stringify_pretty();		
		t1 = clock2::now();
		std::cout << "\nDONE stringify_pretty, elapsed time: " << mil(t1-t0).count() << "ms\n" << std::endl;
		std::cout << stringify_pretty << std::endl;
		free(stringify_pretty);

		std::cout << "After adding a new element to the parsed json\n";
		object_id id_ = parse_doc->get_doc_root();
		char key_[] = {"This_is_the_new_key\0"};
		char val_[] = {"This is the new value added to a parsed document\0"};
		parse_doc->add_value_type(string, id_, key_, val_);
		stringify_pretty = parse_doc->stringify_pretty();
		std::cout << stringify_pretty << std::endl;
		free(stringify_pretty);
		
		delete parse_doc;
	} catch (jsonP_exception &ex) {
		std::cout << "Parse exception parsing text file: " << ex.what() << std::endl;
		delete parse_doc;
	}



	// sample parsing json file using the buffer parser
	std::cout << "\n\n**********************************************************\n";
	std::cout << "sample parsing json file using the buffer parser...\n";
//	jsonP_buffer_parser *buf_parser = new jsonP_buffer_parser{"../samples/med.json", 8192};
	jsonP_buffer_parser *buf_parser = new jsonP_buffer_parser{"../samples/webapp.json", 1000};
	auto buf_t0 = clock2::now();
	jsonP_json *doc_buf = buf_parser->parse();
	auto buf_t1 = clock2::now();
	std::cout << "buffer parser parse time: " << mil(buf_t1-buf_t0).count() << "/ms" << std::endl;
	char *stringify_pretty = doc_buf->stringify_pretty();
	std::cout << "json:\n" << stringify_pretty << std::endl;
	free(stringify_pretty);
	
	delete buf_parser;
	delete doc_buf;
	
	

	// sample streaming json from the net by implementing a custom IChunk_reader interface and supplying it to the buffer parser
//	net_chunk_impl *net_reader = nullptr;
//	jsonP_buffer_parser *net_buf_parser = nullptr;
//	jsonP_json *doc_net_buf = nullptr;
//	
//	try {
//		std::cout << "\n**********************************************************\n\n";
//		std::cout << "Starting buffer_parser test with IChunk_reader implementation net_chunk_impl\n";
//		net_reader = new net_chunk_impl{};
//		net_buf_parser = new jsonP_buffer_parser{net_reader, 8192};
//		doc_net_buf = net_buf_parser->parse();
//		char *pretty = doc_net_buf->stringify_pretty();
//		std::cout << pretty << std::endl;
//		free(pretty);
//		
//		delete doc_net_buf;
//		delete net_buf_parser;
//	} catch (jsonP_exception &ex) {
//		std::cout << "Parse exception: " << ex.what() << ", at: " << net_buf_parser->get_error_index() << std::endl;
//		std::cout << "json snippet:\n" << net_buf_parser->get_error_snip(50, 50) << std::endl;
//		
//		delete doc_net_buf;
//		delete net_buf_parser;
//	
//	}


//	 //sample streaming json from the net by implementing a custom IChunk_reader interface and supplying it to the buffer parser
//	 //and using a push handler to create a compact json object of only keys being looked for
//	modified_json_push_handler_impl *handler_net_push = nullptr;
//	element *net_push_handler_element = nullptr;
//	jsonP_push_parser *net_push_parser = nullptr;
//	
//	try {
//		std::cout << "\n**********************************************************\n\n";
//		std::cout << "Starting buffer_parser test with IChunk_reader implementation net_chunk_impl and the the modified_json_push_handler_impl\n";
//		net_chunk_impl *net_reader2 = new net_chunk_impl{};
//		handler_net_push = new modified_json_push_handler_impl{object};
//		handler_net_push->add_key("/meta/view", "metadata");
//		net_push_parser = new jsonP_push_parser{net_reader2, handler_net_push, 8192};
//		net_push_parser->parse();
//		net_push_handler_element = handler_net_push->get_modified_json();
//		std::string net_push_handler_s;
//		net_push_handler_element->stringify_pretty(net_push_handler_s);
//		std::cout << "\n*** Modified Json ***\n" << net_push_handler_s << std::endl;
//		
//		delete net_push_handler_element;
//		delete handler_net_push;
//		delete net_push_parser;
//		/* jsonP_push_parser owns the IChunk_reader instance, and it will delete it when the parser is deleted */
//	
//	} catch (jsonP_exception &ex) {
//		std::cout << "Parse exception: " << ex.what() << std::endl;
//		
//		delete net_push_handler_element;
//		delete handler_net_push;
//		delete net_push_parser;
//	}
//
//
//
	// sample using the IPush_handler implementation test_push_handler
	std::cout << "\n**********************************************************\n\n";
	std::cout << "Starting push_parser test with IPush_handler implementation test_push_handler\n";
	IPush_handler *handler = new test_push_handler{};
	jsonP_push_parser *push_parser = new jsonP_push_parser{"../samples/sample1.json", handler};
//	jsonP_push_parser *push_parser = new jsonP_push_parser{"/Users/user1/Downloads/large.json", handler};
	auto push_buf_t0 = clock2::now();
	push_parser->parse();
	auto push_buf_t1 = clock2::now();
	
	std::cout << "Done Parsing with push_parser, parse time: " << mil(push_buf_t1-push_buf_t0).count() << "/ms" << std::endl;
	delete push_parser;
	delete handler;

//
//
//	// sample using the IPush_handler implementation modified_json_push_handler_impl
//	std::cout << "\n**********************************************************\n\n";
//	std::cout << "Starting push_parser test with the modified_json_push_handler_impl\n";
//	modified_json_push_handler_impl *handler2 = new modified_json_push_handler_impl{object};
////	handler2->add_key("/glossary/GlossDiv/GlossList/GlossEntry", "GlossDef");
////	handler2->add_key("glossary/GlossDiv/", "title");
//	handler2->add_key("/meta/view", "tableAuthor");
//	handler2->add_key("/meta/view/query", "orderBys");
//	handler2->debug_key_map();
//	jsonP_push_parser *push_parser2 = new jsonP_push_parser{"../samples/sample5.json", handler2};
//	auto push_buf2_t0 = clock2::now();
//	push_parser2->parse();
//	auto push_buf2_t1 = clock2::now();
//	std::cout << "Done Parsing with push_parser, parse time: " << mil(push_buf2_t1-push_buf2_t0).count() << "/ms" << std::endl;
//	element *push_handler_element = handler2->get_modified_json();
//	std::string push_handler_s;
//	push_handler_element->stringify_pretty(push_handler_s);
//	std::cout << "\n" << push_handler_s << std::endl;
//	
//	delete push_handler_element;
//	delete handler2;
//	delete push_parser2;
 
	return 0;
}



jsonP_json * create_json_doc()
{
	jsonP_json *jsonPjson = new jsonP_json{object, 7, 45, 0};
	object_id id = jsonPjson->get_doc_root();
	char key[] = {"mykey\0"};
	char val[] = {"myVal\0"};
	jsonPjson->add_value_type(string, 0, key, val);
	char key2[] = {"mykey_2\0"};
	char val2[] = {"myVal_2\0"};
	jsonPjson->add_value_type(string, 0, key2, val2);
	char key3[] = {"Amykey_3\0"};
	char val3[] = {"AmyVal_3\0"};
	jsonPjson->add_value_type(string, 0, key3, val3);

	char key_[] = {"NEW_KEY\0"};
	char val_[] = {"NEW+_VAL\0"};
	char null_key[] = {"null_key\0"};
	char long_key[] = {"long_key\0"};
	long long_val = 87823750023;
	char double_key[] = {"double_key\0"};
	double double_val = -7729355.09723;
	char bool_t_key[] = {"bool_t_key\0"};
	char bool_f_key[] = {"bool_f_key\0"};
	char obj_key[] = {"new_obj_key\0"};

	object_id new_id = jsonPjson->add_container(obj_key, 1, id, object);

	jsonPjson->add_value_type(string, new_id, key_, val_);
	jsonPjson->add_value_type(null, new_id, null_key);
	jsonPjson->add_value_type(numeric_long, new_id, long_key, &long_val);
	jsonPjson->add_value_type(numeric_double, new_id, double_key, &double_val);
	jsonPjson->add_value_type(bool_true, new_id, bool_t_key);
	jsonPjson->add_value_type(bool_false, new_id, bool_f_key);

	char obj_key_embed[] = {"new_obj_key_embed\0"};
	
	object_id new_id_embed = jsonPjson->add_container(obj_key_embed, 1, new_id, array);
	jsonPjson->add_value_type(string, new_id_embed, NULL, val_);
	jsonPjson->add_value_type(null, new_id_embed, null_key);
	jsonPjson->add_value_type(numeric_long, new_id_embed, NULL, &long_val);

	object_id new_id_embed_embed = jsonPjson->add_container(NULL, 3, new_id_embed, array);
	jsonPjson->add_value_type(string, new_id_embed_embed, NULL, val_);
	jsonPjson->add_value_type(null, new_id_embed_embed, null_key);
	jsonPjson->add_value_type(numeric_long, new_id_embed_embed, NULL, &long_val);

	char string_arry_key[] = {"string_array\0"};
	object_id string_arry = jsonPjson->add_container(string_arry_key, 4, id, array);
	jsonPjson->add_value_type(string, string_arry, NULL, val);
	jsonPjson->add_value_type(null, string_arry, NULL, NULL);
	jsonPjson->add_value_type(numeric_long, string_arry, NULL, &long_val);
	jsonPjson->add_value_type(numeric_double, string_arry, NULL, &double_val);
	jsonPjson->add_value_type(bool_true, string_arry, NULL);
	jsonPjson->add_value_type(bool_false, string_arry, NULL);

	object_id string_arry_embed = jsonPjson->add_container(NULL, 2, string_arry, array);
	jsonPjson->add_value_type(string, string_arry_embed, NULL, val_);
	jsonPjson->add_value_type(null, string_arry_embed, null_key);

	object_id string_arry_embed_obj = jsonPjson->add_container(NULL, 3, string_arry, object);
	jsonPjson->add_value_type(string, string_arry_embed_obj, key_, val_);
	jsonPjson->add_value_type(numeric_long, string_arry_embed_obj, long_key, &long_val);
	jsonPjson->add_value_type(null, string_arry_embed_obj, null_key);


	return jsonPjson;
}

//void print_object(element_object *doc)
//{
//	try {
//		std::cout << "\n\n*** print object ***\n";
//		std::cout << "key1: " << doc->get_as_string("key1") << std::endl;
//		std::cout << "key2: " << doc->get_as_numeric_long("key2") << std::endl;
//		std::cout << "key3: " << doc->get_as_boolean("key3") << std::endl;
//		std::cout << "key3.5: " << doc->get_as_numeric_double("key3.5") << std::endl;
//		
//		std::vector<element*> v = doc->get_as_array("key4");
//		std::cout << "elements of array with key4:" << std::endl;
//		for (element *e : v)
//			std::cout << e->get_string_value() << std::endl;
//			
//		element_object *obj = doc->get_as_object("key6");
//		std::cout << "bools of embedded object with key6\n";
//		std::cout << "sub1: " << obj->get_as_boolean("sub1") << std::endl;
//		std::cout << "sub2: " << obj->get_as_boolean("sub2") << std::endl;
//		std::cout << "sub3: " << obj->get_as_boolean("sub3") << std::endl;
//	
//	} catch (const char *error) { std::cout << "Error: " << error << std::endl; }
//}


char * parse_file(std::string f, std::string &json)
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
		return NULL;
	}
	
	struct stat st;
	
	if (stat(f.c_str(), &st) != 0) {
		std::cerr << "failed to fstat file" << std::endl;
		return NULL;
	}
	
	off_t sz = st.st_size;
	std::cout << "file size: " << sz << std::endl;
	
	char *buf = (char*)malloc(sz+1);
	
//	while (fread((void *)buf, sizeof(char), 4095, fp) > 0) {
//		json += buf;
//	}
	fread((char *)buf, sizeof(char), sz+10, fp);
	buf[sz] = '\0';
	
	fclose(fp);
	
	return buf;
	
	std::cout << f << ", file size: " << strlen(buf) << std::endl;
	
	//testing delete below
//	char *str = json.c_str();
//	int len = json.length();
//	int index = 0;
//	
//	
//	while (((int)str[index] == space || (int)str[index] == tab || (int)str[index] == new_line || 
//			(int)str[index] == car_return) && len > index) 
//		index++;
}


/*
while (((int)json[index] == space || (int)json[index] == tab || (int)json[index] == new_line || 
			(int)json[index] == car_return) && json_length > index) 
		index++;
*/