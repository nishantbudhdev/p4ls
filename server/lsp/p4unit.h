/*
 * -*- c++ -*-
 */

#pragma once

#include "protocol.h"

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

#include <map>
#include <memory>
#include <string>
#include <unordered_map>


struct Collected_data {
	Collected_data(std::vector<Symbol_information>& symbols,
				   std::unordered_map<std::string, std::string>& definitions,
				   std::unordered_map<std::string, std::vector<Text_document_highlight>>& highlights,
				   std::unordered_map<std::string, std::map<Range, std::string>>& locations,
				   std::unordered_map<std::string, std::vector<Symbol_information>::size_type>& indexes)
		: _symbols(symbols)
		, _definitions(definitions)
		, _highlights(highlights)
		, _locations(locations)
		, _indexes(indexes)
	{}
	std::vector<Symbol_information>& _symbols;
	std::unordered_map<std::string, std::string>& _definitions;
	std::unordered_map<std::string, std::vector<Text_document_highlight>>& _highlights;
	std::unordered_map<std::string, std::map<Range, std::string>>& _locations;
	std::unordered_map<std::string, std::vector<Symbol_information>::size_type>& _indexes;
};


class Symbol_collector {
public:
	Symbol_collector(std::string& temp_path, std::string& unit_path, Collected_data& /*output*/)
		: _temp_path(temp_path)
		, _unit_path(unit_path)
		  //, _max_depth(1)
		  //, _symbols(output._symbols)
		  //, _definitions(output._definitions)
		  //, _highlights(output._highlights)
		  //, _locations(output._locations)
		  //, _indexes(output._indexes)
	{
	}
#if 0
	bool preorder(const IR::Node* node) override;
	void postorder(const IR::Node* node) override;
#endif
private:
#if 0
	SYMBOL_KIND get_symbol_kind(const IR::Node* node);
#endif
	std::string _temp_path;
	std::string _unit_path;
	//int _max_depth;
	//std::vector<std::string> _container;
	//std::vector<Symbol_information>& _symbols;
	//std::unordered_map<std::string, std::string>& _definitions;
	//std::unordered_map<std::string, std::vector<Text_document_highlight>>& _highlights;
	//std::unordered_map<std::string, std::map<Range, std::string>>& _locations;
	//std::unordered_map<std::string, std::vector<Symbol_information>::size_type>& _indexes;
};


class Outline {
public:
#if 0
	Outline(CompilerOptions& options, std::string& unit_path, Collected_data& output)
	{
		addPasses({new Symbol_collector(options.file, unit_path, output)});
	}

	void process(std::unique_ptr<const IR::P4Program>& program)
	{
		program->apply(*this);
	}
#endif
};


/**
 *
 */
class P4_file {
public:
	P4_file() = default;
	~P4_file() = default;
	P4_file(const std::string& command, const std::string& unit_path, const std::string& text);
	void change_source_code(const std::vector<Text_document_content_change_event>& content_changes);
	std::vector<Symbol_information>& get_symbols();
	boost::optional<std::string> get_hover(const Location& location);
	boost::optional<std::vector<Text_document_highlight>> get_highlights(const Location& location);

private:
	void compile();

	std::unique_ptr<char[]> _command;
	std::vector<char*> _argv;
#if 0
	std::unique_ptr<const IR::P4Program> _program;
#endif
	std::string _unit_path;
	std::string _source_code;
	std::vector<Symbol_information> _symbols;
	std::unordered_map<std::string, std::string> _definitions;
	/// \brief dictionary of location maps, one for each compilation unit
	/// \detail There may be several units per compiled file, if it
	/// includes other modules.  Each location map binds locations to
	/// symbols found at those locations.
	std::unordered_map<std::string, std::map<Range, std::string>> _locations;
	std::unordered_map<std::string, std::vector<Text_document_highlight>> _highlights;
	std::unordered_map<std::string, std::vector<Symbol_information>::size_type> _indexes;
	bool _changed;
};
