#include "../../include/gitlab-downloader/controllers/ApiController.hpp"
#include "../../include/gitlab-downloader/models/Pipeline.hpp"
#include <json/json.h>

namespace gitlab
{

    void ApiController::getPipelines(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback)
    {
        auto projectId = req->getParameter("project_id");
        if (projectId.empty())
        {
            Json::Value error;
            error["success"] = false;
            error["message"] = "Missing project_id parameter";
            auto resp = drogon::HttpResponse::newHttpJsonResponse(error);
            resp->setStatusCode(drogon::k400BadRequest);
            callback(resp);
            return;
        }

        gitlabService_.getRecentPipelines(projectId, [callback = std::move(callback)](PipelineResponse response)
                                          {
        auto resp = drogon::HttpResponse::newHttpJsonResponse(response.toJson());
        if (!response.success) {
            resp->setStatusCode(drogon::k500InternalServerError);
        }
        callback(resp); });
    }

    void ApiController::downloadArtifact(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback)
    {
        Json::Value response;
        response["message"] = "Not implemented yet";
        auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
        resp->setStatusCode(drogon::k501NotImplemented);
        callback(resp);
    }

} // namespace gitlab