#include"catch.hpp"
#include"game.h"

TEST_CASE(" Tesing play Inline"){

    Game game;
    std::string input;


    SECTION("right input for PlaySideways"){
      input="c3c5d3";
     REQUIRE(game.play(input)==1);
    }

    SECTION("invalid inputs"){
      input="helloworld";
     REQUIRE(game.play(input)==0);
    }
}

TEST_CASE("testing winner","no winner yet"){
  Game game;
  REQUIRE(game.winner().has_value()==false);
}


TEST_CASE("testing getCharAt","starting situation"){

    Game game;
    SECTION("White marbles"){
        Position p1(-2,2,0);
        Position p2(-1,2,-1);
        Position p3(0,2,-2);
    REQUIRE(game.getCharAt(p1)=='O');
    REQUIRE(game.getCharAt(p2)=='O');
    REQUIRE(game.getCharAt(p3)=='O');
   }

    SECTION("black marbles"){
        Position p1(0,-2,2);
        Position p2(1,-2,1);
        Position p3(2,-2,0);
    REQUIRE(game.getCharAt(p1)=='X');
    REQUIRE(game.getCharAt(p2)=='X');
    REQUIRE(game.getCharAt(p3)=='X');
   }
}

TEST_CASE("testing isOver","game just started"){

    Game game;
    REQUIRE(game.isOver()==false);

 SECTION("Player Black just played"){
        game.play("C3C2");
        REQUIRE(game.isOver()==false);
       }

 SECTION("Player white just played"){
        game.play("I8H7");
        REQUIRE(game.isOver()==false);
       }
}


TEST_CASE("testing Winner","nowinner"){
    Game game;
    REQUIRE(!game.winner().has_value());

    SECTION("Player Black just played"){
           REQUIRE(game.current().get()->getColor()==Color::BLACK);
           game.play("C3C2");
           REQUIRE(!game.winner().has_value());
           REQUIRE(game.current().get()->getColor()==Color::WHITE);
          }


}

TEST_CASE("Testing sameMarblesCount","Black just played inline"){
    Game game;
    game.play("C3C4");
    REQUIRE(game.sameMarbleCount()==3);

    SECTION("swapping players and playing inline"){
        game.play("H9G8");
        REQUIRE(game.sameMarbleCount()==1);
    }
}


TEST_CASE("Testing FromAbaProToPosition","black marbles"){
    Game game;

    REQUIRE(game.fromAbaProToPosition("C3")==Position(0,-2,2));
    REQUIRE(game.fromAbaProToPosition("C4")==Position(1,-2,1));
    REQUIRE(game.fromAbaProToPosition("C5")==Position(2,-2,0));

 SECTION("white Player Marbles"){
     REQUIRE(game.fromAbaProToPosition("G5")==Position(-2,2,0));
     REQUIRE(game.fromAbaProToPosition("G6")==Position(-1,2,-1));
     REQUIRE(game.fromAbaProToPosition("G7")==Position(0,2,-2));
  }

}



















