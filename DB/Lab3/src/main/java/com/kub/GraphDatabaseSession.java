package com.kub;

import org.neo4j.driver.Session;

import java.util.ArrayList;

public class GraphDatabaseSession {
    private Session session;

    GraphDatabaseSession(GraphDatabaseDriver driver) {
        session = driver.getSession();
    }

    public void addNodes(ArrayList<Neo4jSimpleNode> nodeList) {
        for (Neo4jSimpleNode node : nodeList) {
            final String QUERY = "CREATE (n:" + node.getLabel() + "{name:\"" + node.getName() + "\"})";
            session.run(QUERY);
        }
    }

    public void addRelations(ArrayList<Neo4jSimpleRelation> relationList) {
        for(Neo4jSimpleRelation relation : relationList) {
            final String QUERY = relation.constructQuery();
            session.run(QUERY);
        }
    }


    public void clearGraph() {
        String CLEAR_GRAPH_QUERY = "match(n) optional match (n)-[r]-() delete n,r";
        session.run(CLEAR_GRAPH_QUERY);
    }

    public void closeSession() {
        session.close();
    }
}
