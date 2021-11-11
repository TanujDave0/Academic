import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Arrays;

import org.junit.jupiter.api.DisplayName;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

class MyTest {
	static DB_Solver2 testSolver;
	static DB_Solver2 testSolver2;
	static Node startNode;
	static Node startNode2;


	@BeforeEach
	void init() {
	    int[] testArray = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray = {1,2,3,4,5,6,7,11,0,9,10,8,12,13,15,14};
		startNode = new Node(testArray);
		startNode2 = new Node(pArray);
		testSolver = new DB_Solver2(startNode, "heuristicOne");
		testSolver2 = new DB_Solver2(startNode2, "heuristicOne");
	}

	@Test
	void zeroTest1() {
		int[] pArray = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		testSolver.moveZero(pArray, 0, 1);
		assertEquals(1, testSolver.findZero(pArray), "Invalid index for zero");
	}

	@Test
	void zeroTest2() {
		int[] pArray = {1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		assertEquals(-1, testSolver.findZero(pArray), "Invalid index for zero");
	}

	@Test
	void goalTest() {
		int[] goalArray = {0,2,1,3,4,5,6,7,8,9,10,11,13,12,15,14};
		int[] goalArray2 = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		int[] solvedArray = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		Node startState = new Node(solvedArray);
		DB_Solver2 solver3 = new DB_Solver2(startState, "heuristicOne");
		assertEquals(false, testSolver.goalTest(goalArray), "Goal array doesn't match");
		assertEquals(false, testSolver.goalTest(goalArray2), "Goal array doesn't match");
		assertEquals(true, solver3.goalTest(solvedArray), "Goal array doesn't match");
	}

	@Test
	void moveTest() {
		int[] pArray = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray1 = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray2 = {1,2,3,8,5,6,7,0,11,9,10,4,12,13,14,15};
		assertEquals(false, testSolver.moveRight(pArray1), "Invalid move");
		assertEquals(true, testSolver.moveLeft(pArray1), "Invalid move");
		assertEquals(1, testSolver.findZero(pArray1), "Invalid move");
		assertEquals(true, testSolver.moveLeft(pArray1), "Invalid move");
		assertEquals(true, testSolver.moveLeft(pArray), "Invalid move");
		assertEquals(false, testSolver.moveDown(pArray2), "Invalid move");
		assertEquals(false, testSolver.moveDown(pArray), "Invalid move");
	}

	@Test
	void moveTest2() {
		int[] pArray = {1,2,3,4,0,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray1 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
		int[] pArray2 = {1,2,3,8,0,5,6,7,11,9,10,4,12,13,14,15};
		assertEquals(false, testSolver.moveRight(pArray1), "Invalid move");
		assertEquals(false, testSolver.moveLeft(pArray1), "Invalid move");
		assertEquals(15, testSolver.findZero(pArray1), "Invalid move");
		assertEquals(false, testSolver.moveLeft(pArray1), "Invalid move");
		assertEquals(false, testSolver.moveLeft(pArray), "Invalid move");
		assertEquals(false, testSolver.moveDown(pArray2), "Invalid move");
		assertEquals(false, testSolver.moveDown(pArray), "Invalid move");
	}

	@Test
	void moveTest3() {
		int[] pArray = {1,2,3,4,0,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray1 = {4,1,2,3,0,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray2 = {1,2,3,8,0,5,6,7,11,9,10,4,12,13,14,15};
		assertEquals(true, testSolver.moveUp(pArray1), "Invalid move");
		assertEquals(false, testSolver.moveUp(pArray), "Invalid move");
		assertEquals(false, testSolver.moveRight(pArray1), "Invalid move");
		assertEquals(false, testSolver.moveLeft(pArray1), "Invalid move");
		assertEquals(4, testSolver.findZero(pArray1), "Invalid move");
		assertEquals(false, testSolver.moveLeft(pArray1), "Invalid move");
		assertEquals(false, testSolver.moveLeft(pArray), "Invalid move");
		assertEquals(false, testSolver.moveDown(pArray2), "Invalid move");
		assertEquals(false, testSolver.moveDown(pArray), "Invalid move");
	}

	@Test
	void getH1Test() {
		
		int[] pArray = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray2 = {1,2,3,4,5,6,7,8,9,10,11,12,13,0,14,15};
		int[] pArray3 = {1,2,3,4,0,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray4 = {1,2,3,4,5,6,7,0,8,9,10,11,12,13,14,15};
		int[] pArray5 = {1,2,3,4,5,6,7,8,9,10,11,12,0,13,14,15};
		
		assertEquals(2, testSolver.getH1(pArray), "Invalid number of out of place tiles");
		assertEquals(14, testSolver.getH1(pArray2), "Invalid number of out of place tiles");
		assertEquals(5, testSolver.getH1(pArray3), "Invalid number of out of place tiles");
		assertEquals(8, testSolver.getH1(pArray4), "Invalid number of out of place tiles");
		assertEquals(13, testSolver.getH1(pArray5), "Invalid number of out of place tiles");
	}

	@Test
	void getH2Test() {
		
		int[] pArray = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray2 = {1,2,3,4,5,6,7,8,9,10,11,12,13,0,14,15};
		int[] pArray3 = {1,2,3,4,0,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray4 = {1,2,3,4,5,6,7,0,8,9,10,11,12,13,14,15};
		int[] pArray5 = {1,2,3,4,5,6,7,8,9,10,11,12,0,13,14,15};
		
		assertEquals(2, testSolver.getH2(pArray), "Invalid Manhattan Distance");
		assertEquals(26, testSolver.getH2(pArray2), "Invalid Manhattan Distance");
		assertEquals(8, testSolver.getH2(pArray3), "Invalid Manhattan Distance");
		assertEquals(14, testSolver.getH2(pArray4), "Invalid Manhattan Distance");
		assertEquals(24, testSolver.getH2(pArray5), "Invalid Manhattan Distance");
	}

	@Test
	void solutionTest() {
		int[] pArray = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		int[] solvedArray = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		assertArrayEquals(solvedArray, testSolver.findSolutionPath().getKey(), "Wrong solution");
		assertArrayEquals(solvedArray, testSolver2.findSolutionPath().getKey(), "Wrong solution");
	}

	@Test
	void solutionTest2() {
		int[] solvedArray = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		assertArrayEquals(solvedArray, testSolver2.findSolutionPath().getKey(), "Wrong solution");
	}	

	@Test
	void copyTest() {
		int[] pArray = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		int[] pArray2 = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
		int[] pArray3 = {9,12,7,4,10,6,0,11,5,13,1,15,3,2,8,14};
		int[] pArray4 = {13,12,7,4,10,6,0,11,5,9,1,15,3,2,8,14};
		assertArrayEquals(pArray, testSolver.copyArray(pArray), "Invalid array copied");
		assertArrayEquals(pArray2, testSolver.copyArray(pArray2), "Invalid array copied");
		assertArrayEquals(pArray3, testSolver.copyArray(pArray3), "Invalid array copied");
		assertArrayEquals(pArray4, testSolver.copyArray(pArray4), "Invalid array copied");
	}
}
