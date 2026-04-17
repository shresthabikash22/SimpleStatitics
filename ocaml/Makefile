OCAMLC = ocamlc
OCAMLOPT = ocamlopt
TARGET = stats
SRC = stats.ml

.PHONY: all native byte run test clean

all: native

native: $(TARGET).native
$(TARGET).native: $(SRC)
	$(OCAMLOPT) -o $(TARGET).native $(SRC)

byte: $(TARGET).byte
$(TARGET).byte: $(SRC)
	$(OCAMLC) -o $(TARGET).byte $(SRC)

run: native
	./$(TARGET).native

test: native
	@printf '5\n1 3 2 3 4\n' | ./$(TARGET).native

clean:
	rm -f $(TARGET).native $(TARGET).byte *.cmi *.cmo *.cmx *.o