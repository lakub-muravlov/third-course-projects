package com.kub;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args){

        String uri = "bolt://localhost:7687";
        String username = "neo4j";
        String password = "admin";

        GraphDatabaseDriver driver = GraphDatabaseDriver.getAndInitDriver(uri, username, password);
        GraphDatabaseSession session = new GraphDatabaseSession(driver);

        session.clearGraph();

        ArrayList<Neo4jSimpleNode> actorList = new ArrayList<>();
        ArrayList<Neo4jSimpleNode> filmList = new ArrayList<>();

        String[] actors = {
                "Keanu Reeves", //0
                "Benedict Cumberbetch",        //1
                "Hugo Weaving",    //2
                "Tilda Swinton",      //3
                "Robert Downey Jr.",   //4
                "Tom Holland", //5
                "Mark Ruffalo" //6
        };

        String[] films = {
                "Matrix", //0
                "Patrick Melrose", //1
                "Avengers: Endgame", //2
                "Constantine", //3
                "Sherlock" //4
        };

        for(String actor :actors) {
            actorList.add(new Neo4jSimpleNode(actor, Label.ACTOR));
        }

        for(String film : films) {
            filmList.add(new Neo4jSimpleNode(film, Label.FILM));
        }


        session.addNodes(actorList);
        session.addNodes(filmList);

        ArrayList<Neo4jSimpleRelation> relationList = new ArrayList<>();
        relationList.add(new Neo4jSimpleRelation(actorList.get(0),filmList.get(0), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(0), filmList.get(3), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(1), filmList.get(1), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(1), filmList.get(3), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(1), filmList.get(4), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(2), filmList.get(0), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(2), filmList.get(1), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(3), filmList.get(2), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(3), filmList.get(3), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(4), filmList.get(2), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(5), filmList.get(2), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(6), filmList.get(2), Relation.PLAYS_IN));
        relationList.add(new Neo4jSimpleRelation(actorList.get(6), actorList.get(2), Relation.LIKES));
        relationList.add(new Neo4jSimpleRelation(actorList.get(0), actorList.get(1), Relation.LIKES));
        session.addRelations(relationList);

        session.closeSession();
        driver.closeDriver();
    }
}
