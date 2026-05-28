# Building with MCP and the Claude API

> [!info] Document Type
> **Type B — Applied Engineering / System Design.** This is a practitioner's guide derived from an Anthropic engineering roundtable on the Model Context Protocol (MCP) and the Claude API. Speakers are core engineers from the API team and the MCP team at Anthropic.

---

## 1. Tổng quan Tài liệu (Executive Summary)

MCP (Model Context Protocol) is Anthropic's open-source standard for connecting large language models to the external world — APIs, data sources, services, hardware, and real-time information. This note synthesizes a deep technical discussion covering: what MCP is and why it was designed as an open standard; the architectural evolution from local-only to remote-hosted servers; how to use MCP natively with the Claude API; the critical and counter-intuitive best practices for MCP tool design; and where the ecosystem is heading.

The central insight is that **MCP tools are prompts** — their names, descriptions, and parameter signatures are not inert metadata, they are part of the text string fed to the model on every request, and treating them as prompt engineering artifacts (not API documentation) is the single highest-leverage improvement most developers can make.

---

## 2. Trích xuất Trọng tâm (Zero-Loss Extraction)

### 2.1 What is MCP — Core Definitions

| Concept | Definition |
|---|---|
| **MCP** | Model Context Protocol — a standard for providing external context to LLMs beyond what fits in the conversation window |
| **MCP Server** | A service that exposes a set of *tools* (functions) that Claude can call to interact with external systems |
| **MCP Client** | The host application (Claude.ai, Claude Code, your API app) that connects to MCP servers and mediates tool calls |
| **Tool** | A single callable function exposed by an MCP server — has a name, description, and parameter schema |
| **Context Window** | The LLM's native "box" — everything Claude can see: conversation history, system prompt, tool definitions, tool results |
| **Remote MCP** | MCP servers hosted at a public URL (e.g., `mcp.github.com`) rather than running locally on the user's machine |
| **MCP Registry** | The central, approved directory of MCP servers maintained by the MCP open-source organization |

---

### 2.2 Architectural Overview

```
Without MCP:
┌─────────────────────────────────┐
│  Conversation History (only)    │
│  ← Claude's entire world       │
└─────────────────────────────────┘

With MCP:
┌────────────────────────────────────────────────────────────┐
│  Conversation History                                       │
│  + Tool Definitions (from MCP servers)                     │
│  + Tool Results (returned from external systems)           │
└────────────────────────────────────────────────────────────┘
           │ Claude calls tools │
           ▼
  ┌─────────────────────────────────────────────────────────┐
  │ MCP Servers (remote or local):                          │
  │   • GitHub (mcp.github.com)    • Asana                  │
  │   • Home automation            • Database               │
  │   • Web browser (Playwright)   • Slack/docs/codebase    │
  └─────────────────────────────────────────────────────────┘
```

---

### 2.3 MCP with the Claude API — Two Integration Paths

| Approach | How It Works | When to Use |
|---|---|---|
| **DIY (MCP SDK)** | Install `@modelcontextprotocol/sdk`, implement the full tool-calling loop manually — parse Claude's tool_use response, call the tool, feed result back | Maximum control; local MCP servers; custom orchestration logic |
| **Native MCP Connector** (new) | Pass MCP server URLs + auth directly in the API call; Anthropic handles the entire call-response loop | Remote MCP servers; minimal glue code; the recommended default for remote servers |

**Native MCP Connector — Conceptual API call structure:**

```python
import anthropic

client = anthropic.Anthropic()

response = client.messages.create(
    model="claude-opus-4-7",
    max_tokens=1024,
    mcp_servers=[
        {
            "type": "url",
            "url": "https://mcp.github.com",
            "authorization_token": "<your_github_token>"
        }
    ],
    messages=[
        {"role": "user", "content": "Show me my latest pull requests"}
    ]
)
```

The API internally:
1. Fetches the tool list from the MCP server
2. Injects tool definitions into the model's context
3. Executes any tool calls Claude makes against the MCP server
4. Returns tool results back to Claude
5. Yields Claude's final response to you

**Developer impact:** Teams have reported **deleting hundreds of lines of tool-calling boilerplate code** after migrating to the native connector.

---

### 2.4 MCP Ecosystem — Notable Servers

| MCP Server | What It Does | Why It Matters |
|---|---|---|
| **GitHub** (`mcp.github.com`) | Full GitHub API access — PRs, issues, repos, code search | Official hosted endpoint; no custom setup required |
| **Context7** | Pulls live documentation from framework/library websites (e.g., Next.js, Anthropic API docs) in `llms.txt` format | Solves LLM knowledge cutoff for rapidly evolving libraries |
| **Playwright** | Drives a real browser — Claude can navigate, screenshot, interact with live web pages | Enables visual feedback loops for UI development |
| **Home Automation** (DIY) | Control smart home devices via natural language | Demonstrates emergent multi-server composition |
| **Knowledge Graph** (experimental) | Two-tool server: `create_memory` + `connect_memory` | Demonstrates how minimal tool surface unlocks emergent Claude behaviours |

---

### 2.5 MCP Evolution Timeline

```
Late 2024:  MCP publicly announced (Anthropic internal protocol, open-sourced)
            ├── Local-only servers (SSE transport, run on user's machine)
            └── Rapid community adoption — fastest-growing open-source protocol

Early 2025: Remote MCP support added
            └── Hosted servers accessible via URL; drastically simpler setup

Mid 2025:   Central MCP Registry launched
            ├── Approved, verified servers indexed publicly
            └── Open standard allows other orgs to extend the registry

Ongoing:    Transition from Anthropic project → industry open-source foundation
            └── Multi-vendor governance; Microsoft, Google, others adopting
```

---

## 3. Giải thích Cặn kẽ (Deep-Dive Explanations)

### 3.1 Why MCP Had to Be an Open Standard (Not a Claude Connector)

The surface-level answer is "interoperability," but the deeper reason is **the combinatorial explosion problem**.

Imagine every AI provider (Anthropic, OpenAI, Google, Grok) builds their own proprietary connector format. Now a company like Asana — which wants to integrate with AI — must build and maintain *N separate connectors* for *N AI providers*. For 5 providers, that is 5× the engineering cost, 5× the maintenance burden, 5× the likelihood of inconsistency.

Proprietary connectors also harm the *user*: if I use Claude and my colleague uses GPT-4, my "Claude Asana connector" does nothing for them. There is no network effect.

An open standard (MCP) collapses this from an $O(N \times M)$ problem (N AI providers × M data sources) to $O(N + M)$: each data source implements MCP once, each AI provider consumes MCP once. This is the same reason HTTP and SQL became universal.

The key insight from Anthropic's decision: **models having external context is good for everyone, including competitors.** Anthropic recognized this as a public good. The "rising tide" framing is operationally accurate — a rich MCP ecosystem benefits every model, which accelerates AI utility for users, which grows the entire market including Anthropic's share of it.

---

### 3.2 The Most Important Insight: MCP Tools ARE Prompts

This is the highest-leverage concept in the entire video and the one most commonly missed by developers.

Every MCP tool you define — its name, its description, its parameter names, the description strings on each parameter — gets serialized into a JSON block and injected directly into the system prompt that Claude reads on *every single API request*. There is no separate "tool processing" step where a different subsystem handles this. It is all one text string.

**Concrete example from the video:**

| Version | Tool Name | Parameter | Description |
|---|---|---|---|
| **Naive** | `generate_image` | `description` | *(none)* |
| **Optimized** | `generate_image` | `prompt` | `"Calls XYZ Diffusion Model v2.1. For best results, use photorealistic, detailed language: specify lighting, style, mood, subject details, background. Avoid abstract single words."` |

Same underlying image generation service. Same Claude model. **No code change.** Yet the optimized version produces dramatically better prompts fed to the diffusion model because Claude now knows:
1. It is talking to a diffusion model (changes its generation strategy)
2. What style of language produces good outputs
3. That "cute puppy" is insufficient — it should expand to a full diffusion prompt

The implication extends further: if you are writing AI-powered applications, *every description string in every JSON schema in your codebase is part of your prompt engineering surface.* This is counterintuitive because descriptions in traditional APIs are documentation for humans. In MCP they are **runtime instructions for the model**.

> [!warning] Common Mistake
> Treating MCP tool descriptions as "docs for developers" rather than "instructions for Claude." The developer never reads these at runtime — Claude does, on every request.

---

### 3.3 Context Pollution — The Anti-Patterns

Context window pollution is one of the most common reasons MCP-based applications underperform. There are three distinct failure modes:

**Failure Mode 1: Too many servers / too many tools**

Each MCP server adds *N* function definitions to the context. Each definition is verbose JSON (name, description, parameters, their types and descriptions). If you connect 10 servers with 10 tools each, you have injected 100 function definitions before the user has said a single word. This:
- Directly reduces the available space for actual conversation and task content
- Costs tokens on every single request (you pay to send all these definitions every time)
- Degrades model decision quality (more choices → more ambiguity)

**Failure Mode 2: Overlapping / ambiguous tools**

If you connect both Linear and Asana simultaneously, both may expose a `get_project_status` tool. Claude has no implicit knowledge of *which* tool to call for a given query. It may call the wrong one, alternate between both, or hallucinate a combined answer. The model lacks the disambiguation context that a human developer would have ("oh this user is talking about their Linear board, not their Asana board").

**Failure Mode 3: Stale context from earlier turns**

A long conversation that started with "what's the weather today?" and moved to "analyze our Q3 revenue" still has all that weather-query context in the window. Old, irrelevant tool results and content dilute the signal-to-noise ratio, making Claude's reasoning about the current task less precise.

**The correct mental model:**

> For each turn of the conversation, ask: *"Which MCP servers are actually needed to respond to the user's current intent?"* Then include only those. Context should be a *scoped* selection, not a permanent accumulation.

---

### 3.4 MCP Server Design — Think Like an LLM, Not Like an API Architect

Traditional REST API design follows the principle of **resource granularity** — one endpoint per operation, narrow contracts, explicit parameters. This produces good developer ergonomics for code-to-code communication.

MCP server design for LLM consumption follows a *different* principle: **intent surface minimization + natural language parameter space**.

**Traditional API surface:**
```
GET /projects
GET /projects/{id}
GET /projects/{id}/tasks
GET /users/{id}
GET /posts/{id}
POST /projects
PUT /projects/{id}
DELETE /projects/{id}
```

**MCP-optimized equivalent:**
```
tool: get_info
  description: "Retrieve information about any entity in this system.
                Specify what you want to know in the 'query' field using
                natural language (e.g., 'all tasks in the Q3 project',
                'user profile for alice@example.com')."
  parameters:
    query: string  # natural language query

tool: mutate
  description: "Create, update, or delete any entity. Describe the
                operation in natural language."
  parameters:
    instruction: string  # natural language operation
```

This collapses 8 endpoints to 2 tools. Claude's natural language understanding replaces the need for parameter enumeration — the model *infers* what API call to make from the intent expressed in the natural language parameter. The result:
1. **Smaller tool surface** → less context consumed, less model confusion
2. **Better interoperability** with other servers (no naming collisions)
3. **Eliminates breaking changes** — you can refactor implementation without changing the tool interface

> [!info] When Granularity Still Matters
> If the model *needs* to make precise, typed decisions (e.g., "the user wants to delete, not create"), narrow tools with explicit enum parameters can still be appropriate. The principle is: **use natural language parameters where the model's language understanding adds more value than strict typing.**

---

### 3.5 MCP's Relaxed Contract Semantics — Why This Is Architecturally Significant

Traditional APIs are **strict contracts**: a change to your API endpoint signature is a *breaking change* that requires versioning, migration guides, and coordination with every consumer.

MCP operates on **intent contracts**: the semantic meaning ("allow Claude to interact with Gmail") is the contract, not the technical implementation details. This means:

- Changing from 15 fine-grained tools to 2 coarse-grained tools is **not a breaking change** — Claude can figure out how to use the new interface because its intent ("interact with Gmail") hasn't changed
- Rewriting descriptions, renaming parameters, merging tools: all non-breaking
- The LLM absorbs implementation churn that would require versioning in a traditional API

This matters for **iteration speed**: you can continuously improve your MCP server through prompt engineering — better descriptions, fewer tools, smarter parameter guidance — and deploy those improvements instantly. No client updates, no version negotiation, no deprecation cycle.

---

### 3.6 Emergent Behavior from MCP Composition

One of the most powerful and least predictable properties of MCP is **emergent cross-server behavior**. When you combine multiple MCP servers in a single context, Claude may find solutions by composing tools across servers in ways the developer never explicitly designed.

**Example:** Connect `gmail_mcp` + `calendar_mcp`. A user asks "remind me about the conference." Claude may:
1. Search Gmail for conference-related emails (via gmail_mcp)
2. Extract the date from the email
3. Check the calendar for that date (via calendar_mcp)
4. Create a calendar reminder
5. Draft a reply confirming attendance

No single server knew about the other. No developer wrote a "conference reminder" workflow. Claude synthesized the behavior from the combined capability surface.

This is the architectural difference between MCP and traditional integration platforms (Zapier, n8n): those require explicit workflow definition ("IF email THEN create calendar event"). MCP + Claude produces workflows from *intent*, requiring only that the relevant tools be present.

The knowledge graph experiment illustrates this at its most extreme: two tools (`create_memory`, `connect_memory`) with no explicit prompting produced an "investigative journalist" mode where Claude proactively builds a structured profile of the user, making connections and surfacing insights from minimal cues.

---

## 4. Tổng hợp & Mở rộng (Key Takeaways & Next Steps)

### Core Takeaways

1. **MCP = Universal LLM-to-World Connector.** It solves the $O(N \times M)$ integration problem by providing a single open standard that any AI provider and any data source can implement once.

2. **MCP Tools are Prompts — Treat Them as Such.** The highest-leverage improvement most developers can make is to write tool names, descriptions, and parameter descriptions as *prompt engineering artifacts*, not as API documentation.

3. **The Native MCP Connector in the Claude API eliminates tool-loop boilerplate.** For remote MCP servers, pass the URL and auth token directly in the API call. Anthropic handles the call-response-feedback loop.

4. **Context discipline is performance engineering.** Be surgical about which servers are active per turn. Every server's tool definitions consume tokens and add to model decision complexity. Fewer, more focused tools outperform many tools of equivalent coverage.

5. **Design MCP servers for models, not for API clients.** Collapse narrow resource-level endpoints into broader, intent-level tools with natural language parameters. The LLM fills in the implementation details.

6. **MCP relaxes API contract semantics.** You can radically refactor your server's tool surface without breaking consumers — because the intent contract (not the technical interface) is what Claude adapts to.

7. **Composition produces emergence.** The value of multiple MCP servers is superlinear — Claude creates cross-server workflows you never designed, solving problems by connecting contexts you would not have thought to connect.

---

### Action Items for AI Engineering Practice

> [!todo] Apply These Immediately
> - [ ] Audit existing MCP tool descriptions as prompt engineering artifacts — rewrite any that are terse API-style docs
> - [ ] Check active server count per API call — can any be conditionally loaded?
> - [ ] Evaluate the `mcp_servers` parameter in Claude API for any projects still running manual tool loops
> - [ ] Explore Context7 MCP for any projects developing against rapidly-evolving frameworks
> - [ ] Design new MCP servers with 1-3 tools max, using natural language parameters instead of many narrow endpoints

---

### Extended Thinking Questions

> [!info] Go Deeper
> 1. **How do you evaluate MCP server quality?** The video predicts that vendors will compete on MCP server quality. What would a rigorous eval harness for an MCP server look like? What metrics matter — task success rate, tool call efficiency (fewest calls to solve the task), token cost per task?
> 2. **What are the security boundaries of MCP?** Remote MCP servers that accept auth tokens raise questions: how does Claude handle confused deputy attacks where a malicious tool instructs Claude to exfiltrate data using another connected tool? What is the defense model?
> 3. **Can MCP tool descriptions be auto-generated or optimized?** Given that descriptions are prompts, could a meta-level process run evaluations, measure task success rates, and propose improved descriptions automatically — an "MCP prompt optimizer"?

---

*Source: "Building with MCP and the Claude API" — Anthropic Developer Relations YouTube. Speakers: Alex (Cloud Relations), Michael (API Team), John (MCP Team). Published mid-2025.*

---

### Related Notes

[[ML_Zoomcamp_1_1]] | [[ML_Zoomcamp_2_2]]

**Hub:** [[Self_Academics/AI_Engineering]]
