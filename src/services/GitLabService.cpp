#include "../../include/gitlab-downloader/GitLabService.hpp"
#include "../../include/gitlab-downloader/models/Pipeline.hpp"
#include <drogon/HttpClient.h>
#include <fmt/format.h>
#include <json/json.h>

namespace gitlab
{

    GitLabService::GitLabService(const std::string &baseUrl, const std::string &token)
        : baseUrl_(baseUrl), token_(token)
    {
        httpClient_ = drogon::HttpClient::newHttpClient(baseUrl);
    }

    void GitLabService::setupRequest(drogon::HttpRequestPtr &req)
    {
        req->addHeader("PRIVATE-TOKEN", token_);
        req->addHeader("Accept", "application/json");
    }

    std::string GitLabService::buildUrl(const std::string &endpoint)
    {
        return fmt::format("{}/api/v4/{}", baseUrl_, endpoint);
    }

    void GitLabService::getRecentPipelines(
        const std::string &projectId,
        std::function<void(PipelineResponse)> &&callback)
    {
        auto req = drogon::HttpRequest::newHttpRequest();
        req->setMethod(drogon::Get);
        req->setPath(buildUrl(fmt::format("projects/{}/pipelines", projectId)));
        setupRequest(req);

        httpClient_->sendRequest(req, [callback = std::move(callback)](drogon::ReqResult result, const drogon::HttpResponsePtr &resp)
                                 {
        if (result == drogon::ReqResult::Ok && resp->getStatusCode() == drogon::k200OK) {
            try {
                Json::Value jsonData;
                Json::Reader reader;
                std::string body = std::string(resp->getBody());




                if (reader.parse(body, jsonData) && jsonData.isArray()) {
                    PipelineResponse response;
                    response.success = true;
                    for (const auto& pipelineJson : jsonData) {
                        response.pipelines.push_back(Pipeline::fromJson(pipelineJson));
                    }
                    callback(std::move(response));
                } else {
                    PipelineResponse response;
                    response.success = false;
                    response.message = "Failed to parse pipeline data";
                    callback(std::move(response));
                }
            } catch (const std::exception& e) {
                PipelineResponse response;
                response.success = false;
                response.message = fmt::format("Error processing response: {}", e.what());
                callback(std::move(response));
            }
        } else {
            PipelineResponse response;
            response.success = false;
            response.message = fmt::format("Failed to fetch pipelines: {}", static_cast<int>(result));
            callback(std::move(response));
        } });
    }

    void GitLabService::downloadArtifact(
        const std::string &projectId,
        const std::string &pipelineId,
        const std::string &artifactPath,
        std::function<void(std::string)> &&callback)
    {
        callback("");
    }

} // namespace gitlab