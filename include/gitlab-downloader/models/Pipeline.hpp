#pragma once
#include <string>
#include <vector>
#include <json/json.h>

namespace gitlab
{

    struct Pipeline
    {
        int id;
        std::string status;
        std::string created_at;
        std::string ref;
        std::vector<std::string> artifacts;

        // Convert to Json::Value
        Json::Value toJson() const
        {
            Json::Value json;
            json["id"] = id;
            json["status"] = status;
            json["created_at"] = created_at;
            json["ref"] = ref;
            Json::Value artifactsJson(Json::arrayValue);
            for (const auto &artifact : artifacts)
            {
                artifactsJson.append(artifact);
            }
            json["artifacts"] = artifactsJson;
            return json;
        }

        // Parse from Json::Value
        static Pipeline fromJson(const Json::Value &json)
        {
            Pipeline pipeline;
            pipeline.id = json["id"].asInt();
            pipeline.status = json["status"].asString();
            pipeline.created_at = json["created_at"].asString();
            pipeline.ref = json["ref"].asString();

            const auto &artifactsJson = json["artifacts"];
            if (artifactsJson.isArray())
            {
                for (const auto &artifact : artifactsJson)
                {
                    pipeline.artifacts.push_back(artifact.asString());
                }
            }
            return pipeline;
        }
    };

    struct PipelineResponse
    {
        std::vector<Pipeline> pipelines;
        bool success{false};
        std::string message;

        // Convert to Json::Value
        Json::Value toJson() const
        {
            Json::Value json;
            json["success"] = success;
            json["message"] = message;

            Json::Value pipelinesJson(Json::arrayValue);
            for (const auto &pipeline : pipelines)
            {
                pipelinesJson.append(pipeline.toJson());
            }
            json["pipelines"] = pipelinesJson;
            return json;
        }
    };

} // namespace gitlab