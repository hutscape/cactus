BOM_PATH?=_data/bill_of_materials.csv

.PHONY: compile upload clean serve install

serve: build
	jekyll serve

build:
	jekyll build

install:
	echo "Installing git-secrets from awslabs..."
	brew install git-secrets
	echo "Adding git-secrets config..."
	cat scripts/git-secrets >> .git/config
	echo "Installing pre-commit hook"
	touch .git/hooks/pre-commit || exit
	echo "Making pre-commit hook executable"
	chmod u+x .git/hooks/pre-commit
	echo "Adding .gitignore..."
	cat scripts/gitignore > .gitignore

bom:
	rm -f $(BOM_PATH)
	python scripts/bom.py hardware/cactus.xml $(BOM_PATH)
	node scripts/bom_info.js
