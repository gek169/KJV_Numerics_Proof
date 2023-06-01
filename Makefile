

vgen:
	cc versegen.c -o vgen

update:
	git add .
	git commit -m "F"
	git push origin main

clean:
	rm -f vgen
