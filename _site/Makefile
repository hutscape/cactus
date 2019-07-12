install:
	echo "Installing git-secrets from awslabs..."
	brew install git-secrets
	echo "Adding git-secrets config..."
	cat scripts/git-secrets >> .git/config
	echo "Installing pre-commit hook"
	touch .git/hooks/pre-commit || exit
	echo "Making pre-commit hook executable"
	chmod u+x .git/hooks/pre-commit

compile:
	arduino-cli compile --fqbn esp8266com:esp8266:d1_mini firmware/

upload: compile
	arduino-cli upload -p /dev/cu.wchusbserial1410 --fqbn esp8266com:esp8266:d1_mini firmware/

clean:
	rm firmware/*.bin
	rm firmware/*.elf

build:
	jekyll build

serve: build
	jekyll serve

.PHONY: compile upload clean
