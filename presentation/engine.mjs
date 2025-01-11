// engine.mjs
import markdownItMark from "markdown-it-mark";
import markdownItContainer from "markdown-it-container";

export default ({ marp }) => marp.use(markdownItMark, markdownItContainer);
