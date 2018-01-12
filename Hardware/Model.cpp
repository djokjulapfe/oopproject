#include "Model.h"
#include <algorithm>

Model::~Model() {
	for (auto &&operation : operations) {
		delete operation;
	}
}

Model *Model::Instance() {
	static Model instance;
	return &instance;
}

Model::Model() {
	Ts = 5;
	Tm = 10;
	Te = 15;
	Mw = 20;
	Mr = 15;
	Nw = 1;
	Nr = 2;
}

void Model::add(Operation *operation) {
	operations.push_back(operation);
}

void Model::remove(Operation *operation) {
	auto position = std::find(operations.begin(), operations.end(), operation);
	if (position != operations.end()) {
		operations.erase(position);
		delete operation;
	}
}

void Model::clear() {
	for (auto &&operation : operations) {
		delete operation;
	}
	operations.clear();
}

Operation *Model::findByName(const Text &name) {
	// TODO: check if multiple ops with same name
	for (auto &&operation : operations) {
		if (operation->getName() == name) {
			return operation;
		}
	}
	return nullptr;
}

Operation *Model::operation(const Text &name) {
	return Instance()->findByName(name);
}

void Model::loadConfig(Text confPath) {
	std::ifstream conf(confPath);
	Text line;
	std::vector<unsigned long> vals;
	if (conf.is_open()) {
		while (std::getline(conf, line)) {
			auto begin = line.find('=') + 1;
//			std::cout << line << std::endl;
//			std::cout << begin << " - " << line.length() << std::endl;
//			std::cout << line.substr(begin, line.length()) << std::endl;
			vals.push_back(std::stoul(line.substr(begin, line.length())));
		}
	}
	conf.close();
	if (vals.size() != 7) {
		return; // TODO: throw exception?
	} else {
		// TODO: remove dependency on configuration order
		Ts = vals[0];
		Tm = vals[1];
		Te = vals[2];
		Mw = vals[3];
		Mr = vals[4];
		Nr = vals[5];
		Nw = vals[6];
	}
}

