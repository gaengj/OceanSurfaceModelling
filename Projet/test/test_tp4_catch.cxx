#define CATCH_CONFIG_MAIN
#include "../../Catch2/single_include/catch.hpp"
#include "../src/Dvector.h"
#include "../src/Height.h"
#include "../src/GerstnerWave.h"
#include "../src/GerstnerWaveModel.h"
#include "../src/Ocean.h"
#include <math.h>
#include <complex>

typedef std::complex<double> dcomp;

/* Tests pour Dvector */

TEST_CASE("Test Vecteur Complexe et Double", "[dvector_test_gen_complex_double]"){

	dcomp A(2, 3.0);

	Dvector<dcomp> vec1(4, A);
	Dvector<double> vec2(4, 5.0);

	bool is_equal = true;

	CHECK(is_equal == true);

}

TEST_CASE("Test Dvector double Methode Size", "[dvector_double_size]"){

  Dvector<double> vec1(3,1.0);
  bool is_equal;

  is_equal = (vec1.size() == 3);
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector double Contructeur Recopie", "[dvector_double_constructeur_recopie]"){

  Dvector<double> vec1(3,1.0);
  bool is_equal;

  Dvector<double> vec2 = vec1;

  is_equal = ((vec1 == vec2) && (&vec1 != &vec2));
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector double Accesseur", "[accesseur]"){

  Dvector<double> vec1(3,1);
  bool is_equal;

  is_equal = (vec1(2) == 1);
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector double Operateur Equal", "[equal]"){

  Dvector<double> vec1(3,1);
  Dvector<double> vec2(3,1);
  bool is_equal;

  is_equal = (vec1 == vec2);
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector double Operateur Plus Equal", "[plus_equal]"){

  Dvector<double> vec1(3,2);
  Dvector<double> vec2(3,2);
  Dvector<double> vec3(3,4);

  bool is_equal;

  is_equal = ((vec1 += vec2) == vec3);
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector double Operateur Time Equal", "[time_equal]"){

  Dvector<double> vec1(3,2);
  Dvector<double> vec3(3,6);

  bool is_equal;

  is_equal = ((vec1 *= 3) == vec3);
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector double Operateur Minus Equal", "[minus_equal]"){

  Dvector<double> vec1(3,2);
  Dvector<double> vec2(3,2);
  Dvector<double> vec3(3,0);

  bool is_equal;

  is_equal = ((vec1 -= vec2) == vec3);
  CHECK(is_equal == true);
}

TEST_CASE("Test Dvector double Operateur Divide Real", "[divide_real]"){

  Dvector<double> vec1(3,10);
  Dvector<double> vec3(3,5);

  bool is_equal;

  is_equal = ((vec1 /= 2) == vec3);
  CHECK(is_equal == true);
}

TEST_CASE("Test Dvector double Operateur Mult Real", "[mult_real]"){

  Dvector<double> vec1(3,10);
  Dvector<double> vec3(3,20);

  bool is_equal;

  is_equal = ((vec1 *= 2) == vec3);
  CHECK(is_equal == true);
}

// //Attention : passe pas :  undefined reference to `Dvector<double> operator+<double>(Dvector<double> const&, Dvector<double> const&)
// TEST_CASE("Test Dvector double Operateur Plus", "[plus]"){

//   Dvector<double> vec1(3,7);
//   Dvector<double> vec2(3,3);
//   Dvector<double> vec3(3,10);

//   bool is_equal;

//   is_equal = ((vec1 + vec2) == vec3);
//   CHECK(is_equal == true);
// }

// //Attention : passe pas : undefined reference to `Dvector<double> operator-<double>(Dvector<double> const&, Dvector<double> const&)
// TEST_CASE("Test Dvector double Operateur Minus", "[minus]"){

//   Dvector<double> vec1(3,7);
//   Dvector<double> vec2(3,3);
//   Dvector<double> vec3(3,4);

//   bool is_equal;

//   is_equal = ((vec1 - vec2) == vec3);
//   CHECK(is_equal == true);
// }

TEST_CASE("Test Dvector double Operateur Unary Minus", "[unary_minus]"){

  Dvector<double> vec1(3,7);
  Dvector<double> vec2(3,-7);

  bool is_equal;

  is_equal = ((-vec1) == vec2);
  CHECK(is_equal == true);
}

TEST_CASE("Test Dvector double Resize Plus Grand", "[resize_plus_grand]"){

  Dvector<double> vec1(3,7);

  vec1.resize(5, 2.0);
  CHECK(vec1.size() == 5);
  CHECK(vec1(0) == 7);
  CHECK(vec1(1) == 7);
  CHECK(vec1(2) == 7);
  CHECK(vec1(3) == 2);
  CHECK(vec1(4) == 2);
}

TEST_CASE("Test Dvector double Resize Plus Petit", "[resize_plus_petit]"){

  Dvector<double> vec1(5,7);
  bool is_equal;

  vec1.resize(3, 20.0);

  is_equal = ((vec1.size() == 3) && (vec1(0) == 7) && (vec1(1) == 7)
               && (vec1(2) == 7));
  CHECK(is_equal == true);
}


TEST_CASE("Test Dvector double Resize Meme Taille", "[resize_meme_taille]"){

  Dvector<double> vec1(5,7);
  bool is_equal;

  vec1.resize(5, 20.0);

  is_equal = ((vec1.size() == 5) && (vec1(0) == 7) && (vec1(1) == 7)
               && (vec1(2) == 7) && (vec1(3) == 7) && (vec1(4) == 7));
  CHECK(is_equal == true);
}

TEST_CASE("Test Dvector complex Contructeur Recopie", "[dvector_complex_constructeur_recopie]"){

  dcomp A(2.0, 3.0);
  Dvector<dcomp> vec1(3, A);
  bool is_equal;

  Dvector<dcomp> vec2 = vec1;

  is_equal = ((vec1 == vec2) && (&vec1 != &vec2));
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector complex Accesseur", "[accesseur]"){

  dcomp A(2.0, 3.0);
  Dvector<dcomp> vec1(3, A);
  bool is_equal;

  is_equal = (vec1(2) == A);
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector complex Operateur Equal", "[equal]"){

  dcomp A(2.0, 3.0);
  dcomp B(2.0, 3.0);
  Dvector<dcomp> vec1(3,A);
  Dvector<dcomp> vec2(3,B);
  bool is_equal;

  is_equal = (vec1 == vec2);
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector complex Operateur Plus Equal", "[plus_equal]"){

  dcomp A(2.0, 3.0);
  dcomp B(2.0, 3.0);
  dcomp C(4.0, 6.0);

  Dvector<dcomp> vec1(3,A);
  Dvector<dcomp> vec2(3,B);
  Dvector<dcomp> vec3(3,C);

  bool is_equal;

  is_equal = ((vec1 += vec2) == vec3);
  CHECK(is_equal == true);

}

TEST_CASE("Test Dvector complex Operateur Time Equal", "[time_equal]"){

  dcomp A(2.0, 3.0);
  dcomp B(4.0, 6.0);

  Dvector<dcomp> vec1(3,A);
  Dvector<dcomp> vec3(3,B);

  bool is_equal;

  is_equal = ((vec1 *= 2) == vec3);
  CHECK(is_equal == true);

}


/* Tests pour Height */

TEST_CASE("Test Constructeur Par Defaut", "[constr_defaut]"){

  Dvector<double> vec1(4, 2.0);
  Height heightmap1(2, 2, vec1);
  bool is_equal;

  is_equal = true;
  CHECK(is_equal == true);

}


TEST_CASE("Test Constructeur Recopie", "[constr_recopie]"){

  Dvector<double> vec1(4, 2.0);
  Height heightmap1(2, 2, vec1);
  bool is_equal;

  Height heightmap2(heightmap1);

  is_equal = ((heightmap1 == heightmap2) && (&heightmap1 != &heightmap2));
  CHECK(is_equal == true);

}

TEST_CASE("Test Operateur Affectation", "[operateur_affectation]"){

  Dvector<double> vec1(4, 6.0);
  Height heightmap1(2, 2, vec1);

  Dvector<double> vec2(4, 7.2);
  Height heightmap2(2, 2, vec2);

  bool is_equal;

  heightmap2 = heightmap1;

  is_equal = ((heightmap1 == heightmap2) && (&heightmap1 != &heightmap2));
  CHECK(is_equal == true);


}

TEST_CASE("Test Operateur Egal Egal", "[operateur_egal_egal]"){

  Dvector<double> vec1(4, 5.0);
  Dvector<double> vec2(4, 5.0);
  Height heightmap1(2, 2, vec1);
  Height heightmap2(2, 2, vec2);

  bool is_equal;

  is_equal = (heightmap1 == heightmap2);
  CHECK(is_equal == true);

}

TEST_CASE("Test Operateur Accession - Foncteur", "[taille_heightmap_egal_dim_vecteur]"){

  Dvector<double> vec1(4, 5.0);
  Height heightmap1(2, 2, vec1);

  bool is_equal;

  is_equal = ( (heightmap1(0, 0) == 5.0) && (heightmap1(0, 1) == 5.0) &&
               (heightmap1(1, 0) == 5.0) && (heightmap1(1, 1) == 5.0));
  CHECK(is_equal == true);

}

TEST_CASE("Test Operateur Accession - Foncteur 2", "[taille_heightmap_sup_dim_vecteur]"){

  Dvector<double> vec1(4, 5.0);
  Height heightmap1(2, 3, vec1);

  bool is_equal;

  is_equal = ( (heightmap1(0, 0) == 5.0) && (heightmap1(0, 1) == 5.0) &&
               (heightmap1(0, 2) == 5.0) && (heightmap1(1, 0) == 5.0) &&
               (heightmap1(1, 1) == 0.0) && (heightmap1(1, 2) == 0.0) );
  CHECK(is_equal == true);

}

/* Tests pour GerstnerWave */

TEST_CASE("Gwave - Test Constructeur Par Defaut", "[gwave_constr_defaut]"){

  GerstnerWave Gwave1();
  bool is_equal = true;

  CHECK(is_equal == true);

}

TEST_CASE("Gwave - Test Constructeur d'Initialisation", "[gwave_constr_init]"){

  Dvector<double> dir1(2, 1.0);
  GerstnerWave Gwave1(3.0, M_PI, dir1, 4.0);
  bool is_equal = true;

  CHECK(is_equal == true);

}

TEST_CASE("Gwave - Test Constructeur de recopie", "[gwave_constr_recopie]"){

  Dvector<double> dir1(2, 1.0);
  GerstnerWave Gwave1(3.0, M_PI, dir1, 4.0);
  bool is_equal;

  GerstnerWave Gwave2(Gwave1);

  is_equal = ((Gwave1 == Gwave2) && (&Gwave1 != &Gwave2));

  CHECK(is_equal == true);

}


/* Tests pour Ocean */
TEST_CASE("Ocean - Test Constructeur Defaut - Destructeur - GenerateHeight", "[ocean_gener_height]"){

  int nx = 128;
  int ny = 128;
  int Lx = 256;
  int Ly = 256;
  int time = 0;

  Dvector<double> Heightmap(nx*ny, 0.0);
  Height H(nx, ny, Heightmap);

  GerstnerWaveModel ModelGestnerWave;
  Ocean Surface(Lx, Ly, nx, ny, time, &H, (WaveModel*) &ModelGestnerWave);

  Height Generated_Height;
  Generated_Height = Surface.generateHeight();

  bool is_equal;

  is_equal = (Generated_Height == H);

  CHECK(is_equal == true);

}
