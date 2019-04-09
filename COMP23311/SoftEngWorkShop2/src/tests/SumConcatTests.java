package tests;

import static org.junit.Assert.*;

import org.junit.Test;

import codeToTest.SumConcatenate;

public class SumConcatTests {
	
	SumConcatenate sc = new SumConcatenate();
	
	@Test
	public void sumOddNumbers() {
		assertEquals(8, sc.sum(1, 7));
	}
	
	@Test
	public void concatStrings() {
		assertEquals("Tejas", sc.link("Tej", "as"));
	}
	
	@Test
	public void typeMisMatch() {
		assertNotEquals(28, sc.link("2", "8"));
	}

}
