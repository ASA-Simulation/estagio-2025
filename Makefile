.PHONY: clean configure build install run backup package help

.DEFAULT_GOAL := help


# Custom variables
PWD := $(shell pwd)
NUM := $(shell nproc)
DATE := $(shell date '+%Y-%m-%d')


clean: ## Clean all generated build files in the project.
	rm -rf ./.cache
	rm -rf ./out/
	rm -rf ./vcpkg
	rm -f compile_commands.json


configure: ## Configure the project for building.
	git submodule update --init --depth 1
	cmake . --preset=debug
	ln -sf $(PWD)/out/build/debug/compile_commands.json $(PWD)/compile_commands.json


build: ## Build all targets in the project.
	cmake --build $(PWD)/out/build/debug --parallel $(NUM)


test: ## Build all targets in the project.
	cmake --build $(PWD)/out/build/debug --parallel $(NUM)


install: ## Install all targets in the project.
	cmake --install $(PWD)/out/build/debug


run: ## Run the application in the project.
	cd $(PWD)/out && LD_LIBRARY_PATH=$(PWD)/out/install/debug/lib exec $(PWD)/out/install/debug/bin/tupa_engine


backup: clean ## Backup the project.
	cd $(PWD)/.. && tar czvf $(DATE).tupa.tar.xz $(PWD)


package: ## Package the project for distribution.
	git submodule update --init --depth 1
	cmake . --preset=release
	ln -sf $(PWD)/out/build/debug/compile_commands.json $(PWD)/compile_commands.json
	cmake --build $(PWD)/out/build/release --parallel $(NUM)
	cmake --install $(PWD)/out/build/release

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
