#pragma once
#include <drogon/HttpController.h>
#include <memory>
#include "gitlab-downloader/GitLabService.hpp"

namespace gitlab
{

    class ApiController : public drogon::HttpController<ApiController>
    {
    public:
        METHOD_LIST_BEGIN
        ADD_METHOD_TO(ApiController::getPipelines, "/api/pipelines", drogon::Get);
        ADD_METHOD_TO(ApiController::downloadArtifact, "/api/artifacts/download", drogon::Post);
        METHOD_LIST_END

        void getPipelines(const drogon::HttpRequestPtr &req,
                          std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void downloadArtifact(const drogon::HttpRequestPtr &req,
                              std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    private:
        GitLabService gitlabService_{"https://gitlab.com", "your-token-here"};
    };

} // namespace gitlab