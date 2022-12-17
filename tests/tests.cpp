#include "objects.h"
#include "gtest/gtest.h"

TEST(Participante, comprobaciones){
	Participante p("i12cacrm@uco.es", "1231231", "Javier Garcia Fernandez", "46072134", "// Grado en Ingeniería Informática", "Telefono", "04012003", "CURSO DE PILOTO");
	EXPECT_TRUE(p.comprobaciones(3, 4));
}
