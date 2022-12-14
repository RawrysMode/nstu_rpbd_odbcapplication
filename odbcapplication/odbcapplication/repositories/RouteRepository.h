#include "Repository.h"
#include "../models/Route.h"
#include "RepositoryHub.h"

#ifndef ROUTE_REPOSITORY_H
#define ROUTE_REPOSITORY_H

using namespace std;


class RouteRepository : public Repository<Route> {

private:
	CityRepository* cityRepository;

public:
	RouteRepository() {}

	RouteRepository(DbConnector dbConnector, CityRepository* cityRepository) {
		this->dbConnector = dbConnector;
		this->cityRepository = cityRepository;
	}

	void checkTableExists() {
		this->dbConnector.querySql("create table if not exists routes (id serial primary key, departure_route_id integer references cities(id) on delete cascade not null, destination_route_id integer references cities(id) on delete cascade not null, route_cost numeric not null);");
	}

	int loadModelsCount();
	int loadModelsCount(string search);

	bool saveModel(Route route) {
		if (!dbConnector.isConnected()) {
			if (route.id == 0) {
				route.id = std::time(0);
				models.push_back(route);
			}
			else {
				vector<Route> newModels = {};
				for (int i = 0; i < models.size(); i++) {
					if (models[i].id == route.id) {
						newModels.push_back(route);
					}
					else {
						newModels.push_back(models[i]);
					}
				}

				models = newModels;
			}


			return true;
		}

		models.push_back(route);
		return route.save(dbConnector.getDBC());
	}
	vector<Route> loadModels();
	vector<Route> loadModels(int offset);
	vector<Route> loadModels(string search);
	vector<Route> loadModels(string search, int offset);

	Route loadModelById(int id) {
		if (!this->dbConnector.isConnected()) {
			for (int i = 0; i < models.size(); i++) {
				if (models[i].id == id) {
					return models[i];
				}
			}

			return Route(id);
		}

		return Route(id).load(this->dbConnector.getDBC());
	}

	void getModelViewRouteData(DialogRoute route, int* totalModelsCount, int* modelPageSize, string search, vector<string>* modelLabels) {
		*totalModelsCount = loadModelsCount(search);
		*modelPageSize = pageSize;
		vector<Route> models = loadModels(search, route.offset * *modelPageSize);
		modelLabels->clear();
		for (int i = 0; i < models.size(); i++) {
			modelLabels->push_back(models[i].toString());
		}
	}
};

#endif